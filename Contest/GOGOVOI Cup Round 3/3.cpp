/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-05 20:10:04
 *    country: Vietnam - VNM
 *    title: 
 *    source: 
 *    submission: 
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
const int N = 1e7;
bitset<N+2> sang;
const ll MOD = 1e9+7;

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    sang[0] = sang[1] = 1;
    for(int i = 2; i * i <= N; i++){
        if(!sang[i]){
            for(int j = i*i; j <= N; j += i) sang[j] = 1;
        }
    }
}

ll legendre(ll n, ll p){
    ll cnt = 0;
    while(n > 0){
        n /= p;
        cnt = (cnt + n)%MOD;
    }
    return cnt;
}

ll phantich(ll n){
    ll ans = 1;
    for(ll i = 2; i <= n; i++){
        if(!sang[i]){
            ll tmp = legendre(n,i)%MOD;
            ans = (ans*((tmp*2)%MOD+1LL)%MOD)%MOD;
        }
    }
    return ans;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    sieve();

    ll n;
    cin >> n;
    cout << phantich(n);
}