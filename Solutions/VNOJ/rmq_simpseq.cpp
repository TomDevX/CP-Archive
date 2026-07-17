/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-18 09:20:06
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Tối giản
 *    source: https://oj.vnoi.info/problem/rmq_simpseq
 *    submission: https://oj.vnoi.info/submission/11900208
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Range Minimum Query
 *    complexity: O(n \log n)
 *    note: We check all elements in array and assume current a[i] is x. We have 2 observations | 1: x must be the only smallest value in our valid array (because all a[j] are multipliers of x and x is unique) | 2: gcd of our valid array must be x (so x will be the divisor of the whole array) => Through these observations, we can iterate through all a[i] and binary lifting it from the left and right to get the furthest left/right endpoint l and r which can make a valid array through [l;i] and [i;r]. To check if they are valid, we use sparse table to query the gcd and the min element. After getting l and r, we combine the ways that we can contribute to the answer
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+2;
int st_min[N][20], st_gcd[N][20];

// ----------------------- [ FUNCTIONS ] -----------------------
int gcd(int a, int b){
    while(b){
        int temp = a%b;
        a = b;
        b = temp;
    }
    return a;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> st_min[i][0];
        st_gcd[i][0] = st_min[i][0];
    }

    for(int k = 1; k <= 19; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st_min[i][k] = min(st_min[i][k-1], st_min[i + (1 << (k-1))][k-1]);
            st_gcd[i][k] = gcd(st_gcd[i][k-1], st_gcd[i + (1 << (k-1))][k-1]);
        }
    }

    ll ans = 0;
    
    for(int i = 1; i <= n; i++){
        int l = i;
        for(int k = 19; k >= 0; k--){
            if(l - (1 << k) <= 0) continue;
            int j = l - (1 << k);
            if(st_min[j][k] > st_min[i][0] && gcd(st_gcd[j][k], st_min[i][0]) == st_min[i][0]){
                l -= (1 << k);
            }
        }

        int r = i;
        for(int k = 19; k >= 0; k--){
            if(r + (1 << k) > n) continue;
            if(st_min[r+1][k] > st_min[i][0] && gcd(st_gcd[r+1][k], st_min[i][0]) == st_min[i][0]){
                r += (1 << k);
            }
        }

        dbg(make_pair(l,r), i);
        ans += (i - l)*(r-i) + (i-l) + (r-i);
    }

    cout << ans;

    return NAH_I_WOULD_WIN;
}