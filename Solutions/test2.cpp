/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-30 22:34:59
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
#include <string>
#include <utility>
#include <map>
#include <set>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("test2.INP", "r")) return;
    freopen("test2.INP", "r", stdin);
    freopen("test2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
bool isIn(int u, int v, int a, int b){
    return a > u && b < v;
}
bool isOut(int u, int v, int a, int b){
    return isIn(a,b,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vi a(2*n+1);
        for(int i = 1; i <= 2*n; i++){
            cin >> a[i];
        }

        vpii pos(n+1);
        vector<bool> checked(n+1);
        map<pii,int> mp;
        for(int i = 1; i <= 2*n; i++){
            if(pos[a[i]].fi) pos[a[i]].se = i;
            else pos[a[i]].fi = i;
        }
        for(int i = 1; i <= n; i++){
            mp[pos[i]] = i;
        }

        int ans = 1;
        for(int i = 0; i < n; i++){
            // if(checked[i]) continue;
            multiset<int> st;
            st.insert(i);
            checked[i] = true;
            int cur = i;
            while(pos[cur].se - pos[cur].fi > 1){
                if(pos[cur].se - pos[cur].fi == 2){
                    st.insert(a[pos[cur].fi+1]);
                    break;
                }
                else{
                    map<pii,int>::iterator it = mp.find({pos[cur].fi+1,pos[cur].se-1});
                    if(it == mp.end()) break;

                    cur = it->se;
                    st.insert(cur);
                    checked[cur] = true;
                }
            }

            int need = 0;
            for(int v : st){
                if(v != need){
                    ans = max(ans, need);
                    break;
                }
                else need++;
            }
        }
        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}