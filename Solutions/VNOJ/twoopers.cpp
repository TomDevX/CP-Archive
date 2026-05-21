/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-21 07:50:44
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: VM 08 Bài 21 - Xử lý xâu
 *    source: https://oj.vnoi.info/problem/twoopers
 *    submission: https://oj.vnoi.info/submission/12349987
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O(n \log n)
 *    note: Notice that we can check every possible circle by doubling the string, so now we double it and check every k. If a == b, we have n ways, else if they only have 1 difference, we have 1 way. To check if they are equal -> use hash. To check if they only have 1 difference, we check there LCP and LCS with hash.
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
    if(!fopen("twoopers.INP", "r")) return;
    freopen("twoopers.INP", "r", stdin);
    freopen("twoopers.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;
const ll M1 = 1234567891;
const ll M2 = 1e9+4567;
const ll base = 31;

struct HashKey{
    ll h1,h2;
    bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
};

HashKey P[N],mem[N + (int)1e5];
int pool = 0;

void init_pow(){
    P[0] = {1,1};
    for(int i = 1; i < N; i++){
        P[i].h1 = (P[i-1].h1*base)%M1;
        P[i].h2 = (P[i-1].h2*base)%M2;
    }
}

struct Hash{
    const string& s;
    int len = 0;
    HashKey *h;

    Hash(const string& _s) : s(_s){
        len = sz(s)-1;

        h = &mem[pool];
        pool += len;

        for(int i = 1; i <= len; i++){
            h[i].h1 = (h[i-1].h1*base + s[i] - 'a' + 1)%M1;
            h[i].h2 = (h[i-1].h2*base + s[i] - 'a' + 1)%M2;
        }
    }

    HashKey get(int l, int r){
        int r1 = (h[r].h1 - h[l-1].h1*P[r-l+1].h1)%M1;
        int r2 = (h[r].h2 - h[l-1].h2*P[r-l+1].h2)%M2;
        if(r1 < 0) r1 += M1;
        if(r2 < 0) r2 += M2;
        return {r1,r2};
    }

    int LCP(int l, int r, Hash& o){ // Longest Common Prefix
        int L = 0, R = r-l, ans = -1;
        while(L <= R){
            int mid = L + ((R-L)>>1);

            if(get(l, l + mid) == o.get(1, mid+1)){
                L = mid+1;
                ans = mid;
            }
            else R = mid-1;
        }
        return ans+1;
    }

    int LCS(int l, int r, Hash& o){ // Longest Common Suffix
        int L = 0, R = r-l, ans = -1;
        while(L <= R){
            int mid = L + ((R-L)>>1);

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
    
    string a,b;
    cin >> a >> b;
    int n = sz(a);
    a = '#' + a + a;
    b = '#' + b;

    Hash ha(a);
    Hash hb(b);

    ll ans = 0;

    for(int k = 0; k < n; k++){
        int lcp = ha.LCP(1 + k, n + k, hb);
        int lcs = ha.LCS(1 + k, n + k, hb);

        dbg(lcp,lcs);

        if(lcp + lcs == 2*n){
            ans += n;
        }
        else if(lcp + lcs == n-1){
            ans++;
        }
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}