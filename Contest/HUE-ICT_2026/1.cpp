/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-08 09:10:17
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
#include <bitset>

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
    if (!fopen("1.INP", "r")) return;
    freopen("1.INP", "r", stdin);
    freopen("1.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6;
bitset<N+2> sang;
int n,m;
vvi a, pref;

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    sang[0] = sang[1] = 1;
    for(int i = 2; i * i <= N; i++){
        if(!sang[i]){
            for(int j = i*i; j <= N; j += i) sang[j] = 1;
        }
    }
}

int get_snt(int x1, int y1, int x2, int y2){
    return pref[x2][y2] - pref[x2][y1-1] - pref[x1-1][y2] + pref[x1-1][y1-1];
}

bool check(int mid){
    for(int i = 1; i <= n-mid+1; i++){
        for(int j = 1; j <= m-mid+1; j++){
            if(get_snt(i,j,i+mid-1,j+mid-1) <= 1) return true;
        }
    }
    return false;
}

// ----------------------- [ CORE LOGIC ] -----------------------
void TomDev_will_AK_VOI(int tc){
    cin >> n >> m;
    a = vvi(n+1,vi(m+1));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) cin >> a[i][j];
    }
    
    pref = vvi(n+1,vi(m+1));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + sang[a[i][j]];
        }
    }

    int l = 1, r = max(n,m);
    int ans = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        
        if(check(mid)){
            ans = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
    cout << ans*ans;
}

int main(){
    fastio;
    setup();

    sieve();
    
    int tc; tc = 1;
    for (int test = 1; test <= tc; test++){
        TomDev_will_AK_VOI(test);
    }
    
    return NAH_I_WOULD_WIN;
}