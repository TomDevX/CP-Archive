/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-19 21:14:30
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Shopping Multilingual
 *    source: https://www.acmicpc.net/problem/13982
 *    submission: https://www.acmicpc.net/source/104101701
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Binary Lifting, RMQ, Sparse Table
 *    complexity: O((n+q) \log n)
 *    note: So we notice that after buying 1 item infinite of time until you can't afford it anymore, that result = your money modulo the price. So that the problem shifted to calculate T after modulo it to each number from left to right in [l;r]. And we have 2 cases: 1. a[i] > T, it won't change T value after the modulo so we don't care | 2. a[i] <= xT it will change the value of x, and it will decrease T at least a half (T/2) when modulo (just think about it because IDK how to prove), so we just need to modulo T about log(T) times until it becomes 0 => So in this problem, we need to find the nearest value in [l;r] which is currently smaller or equal to T, so we use binary lifting to check with RMQ - just like walk on segment tree
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
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
    if(!fopen("13982.INP", "r")) return;
    freopen("13982.INP", "r", stdin);
    freopen("13982.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
ll st[N][19];
int lg[N];

// ----------------------- [ FUNCTIONS ] -----------------------
ll get(int l, int r){
    int k = lg[r-l+1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> st[i][0];
    for(int i = 2; i <= n; i++) lg[i] = lg[i>>1] + 1;

    for(int k = 1; k <= 18; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st[i][k] = min(st[i][k-1], st[i + (1 << (k-1))][k-1]);
        }
    }

    while(q--){
        ll x;
        int l,r;
        cin >> x >> l >> r;

        int cur = l;
        x %= st[cur][0];

        while(get(cur, r) <= x){
            for(int k = 19; k >= 0; k--){ // binary lifting, same to binary search
                if(cur + (1 << k) - 1 <= r && get(cur,cur + (1 << k) - 1) > x){ // if the min in this range is even higher than T, so we skip this range
                    cur += (1 << k);
                }
            }

            x %= st[cur][0];
        }

        cout << x << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}