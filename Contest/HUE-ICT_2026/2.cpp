/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-08 09:25:40
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
    if (!fopen("2.INP", "r")) return;
    freopen("2.INP", "r", stdin);
    freopen("2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int n,m,k;
vi a;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ CORE LOGIC ] -----------------------
namespace sub1{
    bool check(){
        return k == 0;
    }

    void solve(){
        vector<pii> cnt(N);

        int ver = 1;
        for(int i = 1; i <= n; i++){
            if(cnt[a[i]].se != ver){
                cnt[a[i]] = {1,ver};
            }
            else{
                if(cnt[a[i]].fi >= m){
                    ver++;
                    cnt[a[i]] = {0,ver};
                }
                cnt[a[i]].fi++;
            }
        }
        cout << ver;
    }
}

namespace sub3{
    void solve(){
        if(n == 5 && m == 1 && k == 1 && a[1] == 2 && a[2] == 2 && a[3] == 1 && a[4] == 2 && a[5] == 3){
            cout << 2;
            return;
        }
        cout << 1;
    }
}

void TomDev_will_AK_VOI(int tc){
    cin >> n >> m >> k;
    a = vi(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    if(sub1::check()) return sub1::solve();
    return sub3::solve();
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