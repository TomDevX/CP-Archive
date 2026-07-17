/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-04 18:03:17
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Power Products
 *    source: https://codeforces.com/contest/1225/problem/D
 *    submission: https://codeforces.com/contest/1225/submission/377373976
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log maxn)
 *    note: Only prime factors with total exponential (after added 2 factors of 2 numbers together) that modulo k = 0 can be added. To count, store those factors in a map, here I used a devil method to optimize for speed (just dont care about it), to find the needed factors, just get k - p_i
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>
#include <random>
#include <unordered_map>
#include <cmath>

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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("1225D.INP", "r")) return;
    freopen("1225D.INP", "r", stdin);
    freopen("1225D.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;
const unsigned int SPLIT = (1ULL << 32) / 1.0L*((1 + sqrt(5))/2);

random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<ll> dis(1,1e18);

const ll RAND = dis(gen);

int sang[N];
int n,k;

struct custom_hash{
    int operator()(const vpii& a) const{
        unsigned int seed = RAND;
        for(const pair<int,int>& p : a){
            seed ^= p.fi + RAND + SPLIT + (seed << 6) + (seed >> 2);
            seed ^= p.se + RAND + SPLIT + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
unordered_map<vpii,int,custom_hash> mp;

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    iota(all(sang,1),1);
    for(int i = 2; i < N; i++){
        if(sang[i] != i) continue;
        for(int j = i*2; j < N; j += i){
            if(sang[j] == j) sang[j] = i;
        }
    }
}

vpii phantich(int x){
    vpii res;

    while(x > 1){
        int p = sang[x];
        int cnt = 0;
        while(x%p == 0){
            x /= p;
            cnt++;
        }

        cnt %= k;

        if(cnt > 0) res.eb(p,cnt);
    }

    return res;
}

vpii get_contrast(vpii a){
    for(pii& p : a){
        p.se = k-p.se;
    }
    return a;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    sieve();

    cin >> n >> k;

    ll ans = 0;
    for(int i = 1,x; i <= n; i++){
        cin >> x;
        vpii a = phantich(x);
        vpii doi = get_contrast(a);
        ans += mp[doi];
        mp[a]++;
    }

    cout << ans;
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