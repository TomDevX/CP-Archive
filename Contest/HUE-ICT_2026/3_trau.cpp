/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-08 10:06:59
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <deque>
#include <set>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("debuggingz.h")
#include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#ifdef LOCAL
    #include <iomanip>
    #include <ctime>
    #define NAH_I_WOULD_WIN cerr << "\033[32m\n[Runtime: " << fixed << setprecision(3) << 1.0*clock()/CLOCKS_PER_SEC << "s]\033[0m\n", 0
#else
    #define NAH_I_WOULD_WIN 0
#endif

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()

// --- [ TYPES & ALIASES ] ---
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using pii = pair<int,int>;
using pill = pair<int,long long>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if (!fopen("3.INP", "r")) return;
    freopen("3.INP", "r", stdin);
    freopen("3.ANS", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,liml,limr;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ CORE LOGIC ] -----------------------
namespace sub1{
    bool check(){
        return n <= 10000;
    }
    void solve(){
        vector<pii> a(n+1);
        for(int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        vi prefB(n+1), prefG(n+1);
        for(int i = 1; i <= n; i++){
            prefB[i] = prefB[i-1] + a[i].fi;
            prefG[i] = prefG[i-1] + a[i].se;
        }

        vi dp(n+1,-2e9);
        dp[liml] = 0;
        if(prefB[liml] == prefG[liml]) dp[liml] = 0;
        else if(prefB[liml] > prefG[liml]) dp[liml] = 1;
        else dp[liml] = -1;


        for(int i = liml + 1; i <= n; i++){
            for(int j = max(liml+1,i-limr+1); j <= i-liml+1; j++){
                int add = 0;
                int B = prefB[i] - prefB[j-1];
                int G = prefG[i] - prefG[j-1];
                if(B == G) add = 0;
                else if(B > G) add = 1;
                else add = -1;

                dp[i] = max(dp[i], add + dp[j-1]);
            }
        }

        cout << dp[n];
    }
}

namespace sub2{
    const int N = 1e5;
    int st[4*N];
    multiset<int> leaf[N];

    void add_seg(int id, int l, int r, int pos, int val){
        if(l == r){
            leaf[l].insert(val);
            st[id] = *leaf[l].rbegin();
            return;
        }
        
        int mid = l + ((r-l)>>1);
        int left = id<<1;
    
        if(pos <= mid) add_seg(left,l,mid,pos,val);
        else add_seg(left|1,mid+1,r,pos,val);
        st[id] = max(st[left], st[left|1]);
    }
    
    void del_seg(int id, int l, int r, int pos, int val){
        if(l == r){
            leaf[l].erase(leaf[l].find(val));
            st[id] = (leaf[l].empty() ? 0 : *leaf[l].rbegin());
            return;
        }
        
        int mid = l + ((r-l)>>1);
        int left = id<<1;
    
        if(pos <= mid) add_seg(left,l,mid,pos,val);
        else add_seg(left|1,mid+1,r,pos,val);
        st[id] = max(st[left], st[left|1]);
    }
    
    int get(int id, int l, int r, int u, int v){
        if(l > v || r < u) return 0;
        if(l >= u && r <= v){
            return st[id];
        }
    
        int mid = l + ((r-l)>>1);
        int left = id<<1;
    
        return max(get(left,l,mid,u,v), get(left|1,mid+1,r,u,v));
    }

    void solve(){
        vector<pii> a(n+1);
        for(int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        vi prefB(n+1), prefG(n+1);
        for(int i = 1; i <= n; i++){
            prefB[i] = prefB[i-1] + a[i].fi;
            prefG[i] = prefG[i-1] + a[i].se;
        }

        vi prefD(n+1);
        for(int i = 1; i <= n; i++){
            prefD[i] = prefB[i] - prefG[i];
        }
        vi sorted = prefD;
        sort(all(sorted,1));
        for(int i = 1; i <= n; i++) prefD[i] = lower_bound(all(sorted,1), prefD[i]) - sorted.begin();

        vi dp(n+1);
        dp[liml] = 0;
        if(prefB[liml] == prefG[liml]) dp[liml] = 0;
        else if(prefB[liml] > prefG[liml]) dp[liml] = 1;
        else dp[liml] = -1;


        for(int i = liml + 1; i <= n; i++){
            del_seg(1,1,n,prefD[i-limr], dp[i-limr-1]);

            dp[i] = max({get(1,1,n,0,prefD[i]) + 1, get(1,1,n,prefD[i],prefD[i]), get(1,1,n,prefD[i]+1,n) - 1});
            add_seg(1,1,n,prefD[i],dp[i-1]);
        }

        cout << dp[n];
    }
}

void TomDev_will_AK_VOI(int tc){
    cin >> n >> liml >> limr;

    return sub1::solve();
}

int main(){
    fastio;
    setup();
    
    int tc; tc = 1;
    for (int test = 1; test <= tc; test++){
        TomDev_will_AK_VOI(test);
    }
    
    return NAH_I_WOULD_WIN;
}