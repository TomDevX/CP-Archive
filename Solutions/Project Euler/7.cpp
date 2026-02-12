/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-06 23:43:25
 *    country: Vietnam - VNM
 *    title: 10 001st Prime
 *    source: https://projecteuler.net/problem=7
 *    submission: 
 * ----------------------------------------------------------
 *    tags: Level 0
 *    complexity: O(n \log \log n)
 *    note: Use normal sieve with a vector of primes
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
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
const int N = 1e6; // we can guarantee that there are at least 10001 primes from 1 -> 1e6
bitset<N+2> sang;
int ans;
int cnt = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    sang[0] = sang[1] = 1; // 1 means that the number is not prime
    
    for(int i = 2; i * i <= N; i++){
        if(!sang[i]){
            for(int j = i*i; j <= N; j+=i) sang[j] = 1; // i is a divisor of j so j isn't a prime
        }
    }

    for(int i = 2; cnt < 1e4+1; i++){
        cnt += !sang[i];
        if(cnt == 1e4+1) ans = i;
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    sieve();
    cout << ans;
}