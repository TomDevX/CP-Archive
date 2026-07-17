/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-05 22:56:30
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: PON - Prime or Not
 *    source: https://www.spoj.com/problems/PON/
 *    submission: https://www.spoj.com/status/ns=35727953#
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Miller Rabin
 *    complexity: O(k \log^3 n)
 *    note: Typical Miller Rabin
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
    if(!fopen("pon.INP", "r")) return;
    freopen("pon.INP", "r", stdin);
    freopen("pon.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
vi checkSet = {2,3,5,7,11,13,17,19,23,29,31,37};

// ----------------------- [ FUNCTIONS ] -----------------------
ll mul(ll a, ll b, ll MOD){
    ll res = 0;
    while(b){
        if(b&1) res = (res + a)%MOD;
        a = (a+a)%MOD;
        b >>= 1LL;
    }
    return res;
}

ll binpow(ll a, ll b, ll MOD){
    ll res = 1;
    while(b){
        if(b&1) res = mul(res,a,MOD);
        a = mul(a,a,MOD);
        b >>= 1LL;
    }
    return res;
}

bool test(ll a, ll n, ll m, int k){
    ll x = binpow(a,m,n);
    if(x == 1 || x == n-1) return true;
    for(int i = 1; i < k; i++){
        x = mul(x,x,n);
        if(x == n-1) return true;
    }
    return false;
}

bool MLRB(ll n){
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(n % 2 == 0 || n % 3 == 0) return false;
    for(int a : checkSet) if(n == a) return true;

    if(n < 41) return false;

    ll m = n-1;
    int k = 0;
    while(!(m&1)){
        m >>= 1;
        k++;
    }

    for(int a : checkSet){
        if(!test(a,n,m,k)) return false;
    }
    return true;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        ll x;
        cin >> x;
        cout << (MLRB(x) ? "YES" : "NO") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}