/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-30 17:46:03
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Phần tử trung vị - Approach 3
 *    source: https://oj.vnoi.info/problem/median
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
#include <set>
#include <iterator>

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
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("median-3.INP", "r")) return;
    freopen("median-3.INP", "r", stdin);
    freopen("median-3.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int MOD = 65536;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    for(int t = 1 ; t <= tc; t++){
        int seed,mul,add,n,k;
        cin >> seed >> mul >> add >> n >> k;

        vi a(n+1);
        a[1] = seed;
        for(int i = 2; i <= n; i++){
            a[i] = (1LL*a[i-1]*mul + add)%MOD;
        }

        multiset<int> st;
        for(int i = 1; i <= k; i++) st.insert(a[i]);

        multiset<int>::iterator it = next(st.begin(), ((k+1)>>1) - 1);

        ll ans = *it;

        for(int i = k + 1; i <= n; i++){
            st.erase(st.find(a[i-k]));
            if(sz(st)&1){
                
            }
        }
    }
    
    return NAH_I_WOULD_WIN;
}