/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-21 22:42:17
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Palindrome Queries
 *    source: https://cses.fi/problemset/task/2420
 *    submission: https://cses.fi/problemset/result/17253771/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash, Segment Tree
 *    complexity: O(n \log n)
 *    note: We notice that to check if 2 strings are palindrome are not, we need to check it reversed version, so to check fast, we use hash. But what about the update query? -> Use Segment Tree to store hashes, remember to be caution at the length of the merged hash because it is not always r-l+1 but base on the query
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
    if(!fopen("2420.INP", "r")) return;
    freopen("2420.INP", "r", stdin);
    freopen("2420.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;
const ll MOD1 = 1234567891;
const ll MOD2 = 1e9+4567;
const ll base = 31;

struct HashKey{
    ll h1,h2;
    bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
};

HashKey POW[N], mem[N>>1];
HashKey ST[8*N];
int pool = 0, st_pool = 0;

void init_pow(){
    POW[0] = {1,1};
    for(int i =1 ; i  < N; i++){
        POW[i].h1 = (POW[i-1].h1*base)%MOD1;
        POW[i].h2 = (POW[i-1].h2*base)%MOD2;
    }
}

struct Hash{
    const string& s;
    int len = 0;
    HashKey *h = nullptr;
    HashKey *st = nullptr;

    void build(int id, int l, int r){
        if(l == r){
            st[id].h1 = (s[l] - 'a' + 1)%MOD1;
            st[id].h2 = (s[l] - 'a' + 1)%MOD2;
            return;
        }

        int mid = l + ((r-l)>>1);
        int lc = id<<1;

        build(lc,l,mid);
        build(lc|1,mid+1,r);

        st[id] = merge(st[lc],st[lc|1], r - mid);
    }

    HashKey merge(const HashKey& a, const HashKey& b, int len_b){
        HashKey res;

        res.h1 = (a.h1*POW[len_b].h1 + b.h1)%MOD1;
        res.h2 = (a.h2*POW[len_b].h2 + b.h2)%MOD2;

        return res;
    }

    void update(int id, int l, int r, int pos, char val){
        if(l == r){
            st[id].h1 = (val - 'a' + 1)%MOD1;
            st[id].h2 = (val - 'a' + 1)%MOD2;
            return;
        }

        int mid = l + ((r-l)>>1);
        int lc = id<<1;

        if(pos <= mid) update(lc,l,mid,pos,val);
        else update(lc|1,mid+1,r,pos,val);

        st[id] = merge(st[lc],st[lc|1], r - mid);
    }

    pair<HashKey,int> get(int id, int l, int r, int u, int v){
        if(l > v || r < u) return {{0,0},0};
        if(l >= u && r <= v) return {st[id],r-l+1};

        int mid = l + ((r-l)>>1);
        int lc = id<<1;

        pair<HashKey,int> L = get(lc,l,mid,u,v);
        pair<HashKey,int> R = get(lc|1,mid+1,r,u,v);

        if(L.se == 0) return R;
        if(R.se == 0) return L;

        return {merge(L.fi,R.fi,R.se),L.se + R.se}; // L and R length maybe partial so we need a parameter to check
    }

    Hash(const string& _s) : s(_s){
        len = sz(s)-1;
        h = &mem[pool];
        pool += len;

        st = &ST[st_pool];
        st_pool += 4*len;

        build(1,1,len);
    }   
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init_pow();
    
    int n,q;
    cin >> n >> q;
    string a;
    cin >> a;
    a = '#' + a;
    
    Hash h(a);

    string a_rev = a;

    reverse(all(a_rev,1));

    Hash hr(a_rev);

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int pos;
            char c;
            cin >> pos >> c;

            h.update(1,1,n,pos,c);
            hr.update(1,1,n,n-pos+1,c);
        }
        else{
            int l,r;
            cin >> l >> r;

            cout << (h.get(1,1,n,l,r).fi == hr.get(1,1,n,n-r+1,n-l+1).fi ? "YES" : "NO") << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}