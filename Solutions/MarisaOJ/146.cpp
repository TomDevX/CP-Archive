/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-29 09:33:05
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Yet another build array problem
 *    source: https://marisaoj.com/problem/146
 *    submission: https://marisaoj.com/submission/1140570
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming, Sieve
 *    complexity: O(n \cdot k^2)
 *    note: Let dp[i][x] = ways to make an array with i elements and end with x so that every 2 adjacent elements make a prime number
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
    if(!fopen("146.INP", "r")) return;
    freopen("146.INP", "r", stdin);
    freopen("146.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7;
const int K = 3000; // must be a bit higher because there are 2 numbers add up to K
int sang[K+2];
ll dp[102][1002];
vi primes;

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    sang[0] = sang[1] = 1;
    for(int i = 2; i * i <= K; i++){
        if(!sang[i]){
            for(int j = i*i; j <= K; j+=i) sang[j] = 1;
        }
    }
    primes.reserve(1000);
    for(int i = 2; i <= K; i++){
        if(!sang[i]) primes.eb(i);
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    sieve();
    
    int n,k;
    cin >> n >> k;

    for(int x = 0; x <= k; x++) dp[1][x] = 1;

    for(int i = 2; i <= n; i++){
        for(int p : primes){
            if(p > 2*k) break; // because it will be useless if x or p-x is > k
            for(int x = 0; x <= min(k,p); x++){
                if(p - x >= k) dp[i][x] = (dp[i][x] + dp[i-1][p-x])%MOD;
            }
        }
    }

    ll ans = 0;
    for(int x = 0; x <= k; x++) ans = (ans + dp[n][x])%MOD;
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}