/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-12 16:48:59
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Bài 5: Đếm cặp số nguyên tố cùng nhau
 *    source: https://oj.vnoi.info/problem/gogovoi_nangcao_ntcungnhau
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
    if(!fopen("gogovoi_nangcao_ntcungnhau.INP", "r")) return;
    freopen("gogovoi_nangcao_ntcungnhau.INP", "r", stdin);
    freopen("gogovoi_nangcao_ntcungnhau.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2, M = 1e6+2;

int a[N];
ll cnt[M];

// ----------------------- [ FUNCTIONS ] -----------------------
ll nck(ll x){
    return x*(x-1)/2;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    int max_val = 0;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
        cnt[a[i]]++;
        max_val = max(max_val, a[i]);
    }

    for(int d = 1; d <= max_val; d++){
        for(int j = d << 1; j <= max_val; j += d){
            cnt[d] += cnt[j];
        }
    }

    for(int i = max_val; i >= 1; i--){
        cnt[i] = nck(cnt[i]);
        for(int d = i << 1; d <= max_val; d += i) cnt[i] -= cnt[d];
    }

    cout << cnt[1];
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
