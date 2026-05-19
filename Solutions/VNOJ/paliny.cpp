/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-19 08:49:31
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Palindrome dài nhất
 *    source: https://oj.vnoi.info/problem/paliny
 *    submission: https://oj.vnoi.info/submission/12338521
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O(n \log n)
 *    note: Just binary search on the length
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
    if(!fopen("paliny.INP", "r")) return;
    freopen("paliny.INP", "r", stdin);
    freopen("paliny.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e4+5;

ll hashS[N], hashSr[N], POW[N];
const ll MOD = 1234567891;
ll base = 31;

string s, sR;
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    POW[0] = 1;
    for(int i = 1; i <= n; i++){
        POW[i] = (POW[i-1]*base)%MOD;
    }
}

void make_hash(){
    sR = s;
    reverse(all(sR,1));

    for(int i = 1; i <= n; i++){
        hashS[i] = (hashS[i-1]*base + s[i] - 'a' + 1)%MOD;
        hashSr[i] = (hashSr[i-1]*base + sR[i] - 'a' + 1)%MOD;
    }
}

ll get(int l, int r){
    return ((hashS[r] - hashS[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

ll getR(int l, int r){
    l = n-l+1;
    r = n-r+1;
    swap(l,r);
    return ((hashSr[r] - hashSr[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

bool check(int len){
    for(int i = 1; i + len - 1 <= n; i++){
        int j = i + len - 1;
        if(get(i, j) == getR(i,j)) return true;
    }

    return false;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    cin >> s;
    s = '#' + s;

    init();
    make_hash();

    // one center
    int l = 1, r = n, ans = 1;
    int prev = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        if(!(mid&1)) mid++;
        if(mid == prev) break;
        prev = mid;

        if(check(mid)){
            l = mid+1;
            ans = mid;
        }
        else r = mid-1;
    }


    // 2 center
    l = 1, r = n;
    prev = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        if(mid&1) mid++;

        if(mid == prev) break;
        prev = mid;

        if(check(mid)){
            l = mid+1;
            ans = max(ans,mid);
        }
        else r =  mid-1;
    }

    cout << ans;


    return NAH_I_WOULD_WIN;
}