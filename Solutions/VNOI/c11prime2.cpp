/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-09 22:35:26
 *    country: Vietnam - VNM
 *    title: Số nguyên tố 2
 *    source: https://oj.vnoi.info/problem/c11prime
 *    submission: https://oj.vnoi.info/submission/11679434
 * ----------------------------------------------------------
 *    tags: Number theory
 *    complexity: O(60*\log{10^9}*12*\log^3{n})
 *    note: We iterate through all possible exponent (in this case 1 -> 60 is good for 10^18), and then binary search to find the base, then use Miller Rabin to check if it is prime. We only need to bin search from 1 -> 1e9 because sqrt(1e18) = 1e9 (because due to the problem states that the exponent must > 1 so that means 1e9^2 is the maximum prime factor)
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
vector<ull> checkSet = {2,3,5,7,11,13,17,19,23,29,31,37};

// ----------------------- [ FUNCTIONS ] -----------------------
ull mul(ull a, ull b, ull MOD){
    ull res = 0;
    while(b){
        if(b&1){
            res = (res + a)%MOD;
        }
        a = (a+a)%MOD;
        b >>= 1;
    }
    return res;
}


ull binpow(ull a, ull b, ull MOD){
    ull res = 1;
    while(b){
        if(b&1){
            if(MOD == (ull)9e18 && (ull)9e18/a <= res) return 9e18;
            res = mul(res,a,MOD);
        }
        b >>= 1;
        if(!b) return res;
        if(MOD == (ull)9e18 && (ull)9e18/a <= a) return 9e18;
        a = mul(a,a,MOD);
    }
    return res;
}

ull get_base(ull n, int e){
    int l = 1, r = 1e9;
    int ans = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        if(binpow(mid,e,9e18) >= n){
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return ans;
}

bool test(ull a, ull m, ull n, int k){
    ull x = binpow(a,m,n);
    if(x == 1 || x == n-1) return true;
    for(int i = 1; i < k; i++){
        x = mul(x,x,n);
        if(x == n-1) return true;
    }
    return false;
}

bool Miller_Rabin(ull n){
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(n % 2 == 0 || n % 3 == 0) return false;

    for(ull a : checkSet) if(n == a) return true;
    if(n < 41) return false;

    ull m = n-1;
    int k = 0;

    while(!(m&1)){
        m >>= 1;
        k++;
    }

    for(ull a : checkSet){
        if(!test(a,m,n,k)) return false;
    }
    return true;
}

bool check(ull n, int e){
    ull base = get_base(n,e);
    return binpow(base,e,9e18) == n && Miller_Rabin(base);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    ull n;
    cin >> n;

    for(int e = 2; e <= 60; e++){
        if(check(n,e)){
            cout << get_base(n,e) << ' ' << e;
            return 0;
        }
    }
    cout << 0;
}