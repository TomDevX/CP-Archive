/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-21 08:37:54
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tìm xâu
 *    source: https://oj.vnoi.info/problem/v11str
 *    submission: https://oj.vnoi.info/submission/12350481
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O(n \log n) 
 *    note: To check if the string is different at most 1 error fast, we use LCP (Longest Common Prefix) and LCS (Longest Common Suffix) on hash
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
    if(!fopen("v11str.INP", "r")) return;
    freopen("v11str.INP", "r", stdin);
    freopen("v11str.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;
const ll MOD1 = 1234567891;
const ll MOD2 = 1234567891;
const ll base = 31;

struct HashKey{
    ll h1,h2;
    bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
};

HashKey POW[N], mem[N+1005];
int pool = 0;

void init_pow(){
    POW[0] = {1,1};
    for(int i = 1; i < N; i++){
        POW[i].h1 = (POW[i-1].h1*base)%MOD1;
        POW[i].h2 = (POW[i-1].h2*base)%MOD2;
    }
}

struct Hash{
    int len = 0;
    HashKey* h = nullptr;

    Hash(int n) : len(n){
        h = &mem[pool];
        pool += n;

        int x;
        for(int i = 1; i <= n; i++){
            cin >> x;
            h[i].h1 = (h[i-1].h1*base + x + 1)%MOD1;
            h[i].h2 = (h[i-1].h2*base + x + 1)%MOD2;
        }
    }

    HashKey get(int l, int r){
        int r1 = (h[r].h1 - h[l-1].h1*POW[r-l+1].h1)%MOD1;
        int r2 = (h[r].h2 - h[l-1].h2*POW[r-l+1].h2)%MOD2;
        if(r1 < 0) r1 += MOD1;
        if(r2 < 0) r2 += MOD2;
        return {r1,r2};
    }

    int LCP(int l, int r, Hash& o){
        int L = 0, R = r-l, ans = -1;
        while(L <= R){
            int mid = L  + ((R-L)>>1);

            if(get(l, l + mid) == o.get(1, mid + 1)){
                L = mid+1;
                ans = mid;
            }
            else R = mid-1;
        }

        return ans+1;
    }

    int LCS(int l, int r, Hash& o){
        int L = 0, R = r-l, ans = -1;
        while(L <= R){
            int mid = L  + ((R-L)>>1);

            if(get(r - mid, r) == o.get(o.len - mid, o.len)){
                L = mid+1;
                ans = mid;
            }
            else R = mid-1;
        }

        return ans+1;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init_pow();
    
    int n,m;
    cin >> n >> m;

    Hash ha(n);
    Hash hb(m);

    for(int i = 1; i + n - 1 <= m; i++){
        int lcp = hb.LCP(i, i + n - 1, ha);
        if(lcp >= n-1 || hb.get(i + lcp + 1, i + n - 1) == ha.get(lcp+2,n)){
            cout << i;
            return 0;
        }
    }
    cout << -1;
    
    return NAH_I_WOULD_WIN;
}