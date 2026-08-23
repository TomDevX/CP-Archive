/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-08-16 09:39:53
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Giàn Hoa Của Nhật Trường
 *    source: https://oj.iuhcoder.com/problem/ctsqn80
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
    if(!fopen("ctsqn80.INP", "r")) return;
    freopen("ctsqn80.INP", "r", stdin);
    freopen("ctsqn80.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;

int a[N];
int suffmin[N];
int bigger_than_R_idx[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
int get_min_idx(int l, int r, int val){
    int res = n+1;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        if(suffmin[mid] > val){
            r = mid-1;
        }
        else{
            l = mid+1;
            res = mid;
        }
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    suffmin[n+1] = 1e9;
    bigger_than_R_idx[n+1] = n+1;
    for(int i = n; i >= 1; i--){
        suffmin[i] = min(suffmin[i+1], a[i]);
        bigger_than_R_idx[i] = (a[i] > i ? i : bigger_than_R_idx[i+1]);
    }

    ll ans = 0;
    for(int l = 1; l <= n; l++){
        int L = get_min_idx(l, n+1, l);
        int R = bigger_than_R_idx[l] - 1;
        dbg(make_pair(L,R),l);
        ans += max(0,min(L,R) - l +1);
    }
    cout << ans << '\n';
}

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}