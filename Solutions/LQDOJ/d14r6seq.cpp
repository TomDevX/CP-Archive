/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-22 10:04:37
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Dãy số (Contest Practice VNOI 2021 Round 6)
 *    source: https://lqdoj.edu.vn/problem/d14r6seq
 *    submission: https://lqdoj.edu.vn/submission/8635139
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash, Binary Search
 *    complexity: O(n \log n)
 *    note: We have 3 queries, first one is find substring with most freq (frequency), second is find 1 but with longest length, third is find second but at last index. So the first one is obvious that we just need to check which substring of lenght 1 (1 character) has most freq, because it always appears the most, we use the length of 1 to binary search the length on 2 (substring which has same freq will be good) -> to check freq faster, we hash the string and put them in arr and count freq, then the last is the easiest -> just iterate through all substring with best_len which has best_freq and get it at the last index
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("d14r6seq.INP", "r")) return;
    freopen("d14r6seq.INP", "r", stdin);
    freopen("d14r6seq.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;
const ll MOD1 = 1234567891;
const ll MOD2 = 1e9+4567;
const ll base = 31;

struct HashKey{
    ll h1,h2;
    bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
    bool operator<(const HashKey& o) const{
        return (h1 != o.h1 ? h1 < o.h1 : h2 < o.h2);
    }
};

bool cmp(const pair<HashKey,int>& p1, const pair<HashKey,int>& p2){
    if(!(p1.fi == p2.fi)) return p1.fi < p2.fi;
    return p1.se < p2.se;
}

int a[N], cnt[N];
pair<HashKey,int> hashes[N];
HashKey POW[N], mem[N];
int n;

struct Hash{
    Hash(){}   
    
    void init(){
        for(int i = 1; i <= n; i++){
            mem[i].h1 = (mem[i-1].h1*base + a[i] + 1)%MOD1;
            mem[i].h2 = (mem[i-1].h2*base + a[i] + 1)%MOD2;
        }
    }
    
    HashKey get(int l, int r){
        int r1 = (mem[r].h1 - mem[l-1].h1*POW[r-l+1].h1)%MOD1;
        int r2 = (mem[r].h2 - mem[l-1].h2*POW[r-l+1].h2)%MOD2;
        if(r1 < 0) r1 += MOD1;
        if(r2 < 0) r2 += MOD2;
        return {r1,r2};
    }
} ha;

// ----------------------- [ FUNCTIONS ] -----------------------
void init_pow(){
    POW[0] = {1,1};
    for(int i = 1; i < N; i++){
        POW[i].h1 = (POW[i-1].h1*base)%MOD1;
        POW[i].h2 = (POW[i-1].h2*base)%MOD2;
    }
}

bool isValid(int len, int freq){
    for(int i = 1; i + len - 1 <= n; i++){
        hashes[i] = {ha.get(i, i + len - 1), i};
    }

    sort(sub(hashes,1,n-len+1),cmp);

    int cnt = 1;
    for(int i = 2; i + len - 1 <= n; i++){
        if(!(hashes[i].fi == hashes[i-1].fi)){
            if(cnt >= freq) return true;
            cnt = 0;
        }
        cnt++;
    }

    return cnt >= freq;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init_pow();
    
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    ha.init();

    sort(sub(a,1,n));

    // find freq
    
    int ans_freq = 0;
    int cnt = 1;
    for(int i = 2; i <= n; i++){
        if(a[i] != a[i-1]){
            ans_freq = max(ans_freq,cnt);
            cnt = 0;
        }
        cnt++;
    }
    ans_freq = max(ans_freq,cnt);

    // find length

    int ansL = 0;
    int l = 1, r = n-ans_freq+1;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        
        if(isValid(mid,ans_freq)){
            ansL = mid;
            l = mid+1;
        }
        else r = mid-1;
    }

    // find position

    for(int i = 1; i + ansL - 1 <= n; i++){
        hashes[i] = {ha.get(i, i + ansL - 1), i};
    }

    sort(sub(hashes,1,n-ansL+1),cmp);

    int pos = 0;
    cnt = 1;
    for(int i = 2; i + ansL - 1 <= n; i++){
        if(!(hashes[i].fi == hashes[i-1].fi)){
            if(cnt >= ans_freq){
                pos = hashes[i-1].se;
            }
            cnt = 0;
        }
        cnt++;
    }
    
    if(cnt >= ans_freq){
        pos = hashes[n - ansL + 1].se;
    }

    cout << pos << ' ' << pos + ansL - 1;
    
    return NAH_I_WOULD_WIN;
}