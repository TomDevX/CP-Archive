/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-05 17:56:59
 *    country: Vietnam - VNM
 *    title: Hamming Distance
 *    source: https://cses.fi/problemset/task/2136
 *    submission: https://cses.fi/paste/9254599d71bb5d60f6b997/
 * ----------------------------------------------------------
 *    tags: bit
 *    complexity: O(n^2)
 *    note: A^B will eliminate the same bit and keep the different bits, so that we can use popcount to count each pair of string after turning them into int
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#include <algorithm>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,k;
    cin >> n >> k;
    vector<string> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    vi b(n+1);
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < k; j++){
            if(a[i][j] == '1') b[i] += (1 << j);
        }
    }

    int cnt = 1e9;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i; j++){
            cnt = min(cnt,__builtin_popcount(b[i]^b[j]));
        }
    }

    cout << cnt;
}