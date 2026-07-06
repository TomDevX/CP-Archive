/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-06 08:52:53
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Bài 2: Đếm số bội 2
 *    source: https://oj.vnoi.info/problem/gogovoi_nangcao_demsoboi2
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>

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
    if(!fopen("gogovoi_nangcao_demsoboi2.INP", "r")) return;
    freopen("gogovoi_nangcao_demsoboi2.INP", "r", stdin);
    freopen("gogovoi_nangcao_demsoboi2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 21;

int ele[N];
int n;
ull K;

// ----------------------- [ FUNCTIONS ] -----------------------
ull gcd(ull a, ull b){
    while(b){
        ull tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

ull lcm(ull a, ull b) {
    if(a/gcd(a,b) >= (K+b)/b) return K+1;
    return a / gcd(a,b) * b;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> K;
    for(int i = 0; i < n; i++) cin >> ele[i];

    ull ans1 = 0, ans2 = 0;
    for(int mask = 1; mask < (1 << n); mask++){
        ull cur = 1;
        for(int i = 0; i < n; i++){
            if(mask >> i & 1){
                cur = lcm(ele[i],cur);
                if(cur > K){
                    cur = K+1;
                    break;
                }
            }
        }

        int cnt = __builtin_popcount(mask);
        dbg(cur,1);
        ull tmp = K/cur;
        
        if(cnt&1){
            ans1 += tmp;
            ans2 += tmp*cnt;
        }
        else{
            ans1 -= tmp;
            ans2 -= tmp*cnt;
        }
        dbg(mask,1);
    }

    cout << ans1 << ' ' << ans2;
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}