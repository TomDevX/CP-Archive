/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-21 17:21:51
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: ANAGRAM
 *    source: https://oj.vnoi.info/problem/fc051_anagram
 *    submission: https://oj.vnoi.info/submission/12355090
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O((n + m) \log n)
 *    note: The obvious way to check if 2 substrings are anagram is to check the frequency of their characters, to check it we make a prefix sum of 26 characters and just binary search on the length. But that would take us n*m*log2(min(n,m))*26 -> TLE. So instead of Checking every status one by one with each other, we can put it in the unordered_set to check if it is already appeared in the other string, but to insert an vector/array into unordered_set is very complex and takes more time complexity, so we can hash it (hash the arr[26] frequency), and put it into the unordered set
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <unordered_set>
#include <random>

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
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("fc051_anagram.INP", "r")) return;
    freopen("fc051_anagram.INP", "r", stdin);
    freopen("fc051_anagram.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<ll> dist(1,1e18);
const int RAND = dist(gen);

const int N = 4005;
const ll MOD1 = 1234567891;
const ll MOD2 = 1e9+4567;
const ll base = 31;

struct HashKey{
    ll h1,h2;
    bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
};

struct custom_hash{
    int operator()(const HashKey& x) const{
        return (x.h1*31 + x.h2)^RAND;
    }
};


HashKey POW[N];

void init_pow(){
    POW[0] = {1,1};
    for(int i = 1; i < N; i++){
        POW[i].h1 = (POW[i-1].h1*base)%MOD1;
        POW[i].h2 = (POW[i-1].h2*base)%MOD2;
    }
}

string a,b;
int n,m;
HashKey Hash;

// ----------------------- [ FUNCTIONS ] -----------------------
void Add(char c){
    Hash.h1 = (Hash.h1 + POW[25 - (c - 'a') + 1].h1)%MOD1;
    Hash.h2 = (Hash.h2 + POW[25 - (c - 'a') + 1].h2)%MOD2;
}

void Remove(char c){
    Hash.h1 = (Hash.h1 - POW[25 - (c - 'a') + 1].h1)%MOD1;
    Hash.h2 = (Hash.h2 - POW[25 - (c - 'a') + 1].h2)%MOD2;
    if(Hash.h1 < 0) Hash.h1 += MOD1;
    if(Hash.h2 < 0) Hash.h2 += MOD2;
}

bool check(int len){
    static unordered_set<HashKey,custom_hash> st;
    st.clear();
    st.reserve(N - len);
    Hash = {0,0};


    for(int j = 1; j <= len; j++){
        Add(b[j]);
    }
    st.insert(Hash);

    for(int j = len+1; j <= m; j++){
        Remove(b[j-len]);
        Add(b[j]);
        st.insert(Hash);
    }

    Hash = {0,0};

    for(int i = 1; i <= len; i++){
        Add(a[i]);
    }

    if(st.count(Hash)) return true;

    for(int i = len+1; i <= n; i++){
        Remove(a[i-len]);
        Add(a[i]);
        if(st.count(Hash)) return true;
    }

    return false;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init_pow();
    
    cin >> a >> b;
    n = sz(a), m = sz(b);
    a = '#' + a;
    b = '#' + b;

    int l = 1, r = min(n,m), ans = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        if(check(mid)){
            l = mid+1;
            ans = mid;
        }
        else r = mid-1;
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}