/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-19 22:02:57
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: VOI 13 Bài 4 - Xử lý xâu
 *    source: https://oj.vnoi.info/problem/vostr
 *    submission: https://oj.vnoi.info/submission/12342748
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O(n \log n)
 *    note: The one character which determine if the string is smaller/greater is the first different character. So now in order to improve time complexity, we just need to use binary search and hash to find the last same position of 2 strings, then we examine the first different character.
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
    if(!fopen("vostr.INP", "r")) return;
    freopen("vostr.INP", "r", stdin);
    freopen("vostr.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5;

int n,m;
string a,b;

const ll MOD = 1234567891;
ll POW[N], hashA[N], hashB[N];
ll base = 31;

// ----------------------- [ FUNCTIONS ] -----------------------
void make_hash(){
    POW[0] = 1;
    for(int i = 1; i <= max(n,m); i++){
        POW[i] = (POW[i-1]*base)%MOD;
    }

    for(int i = 1; i <= n; i++){
        hashA[i] = (hashA[i-1]*base + a[i] - 'a' + 1)%MOD;
    }
    for(int i = 1; i <= m; i++){
        hashB[i] = (hashB[i-1]*base + b[i] - 'a' + 1)%MOD;
    };
}

ll getA(int l, int r){
    return ((hashA[r] - hashA[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

ll getB(int l, int r){
    return ((hashB[r] - hashB[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

int longest_pref(int l, int r, int u, int v){
    int L = 0, R = min(v-u,r-l), ans = 0;

    while(L <= R){
        int mid = L + ((R-L)>>1);

        if(getA(l, l + mid) == getB(u, u + mid)){
            ans = mid;
            L = mid+1;
        }
        else R = mid-1;
    }
    return ans;
}

char check(int l, int r, int u, int v){
    if(r-l == v-u){
        if(getA(l,r) == getB(u,v)) return '=';
        int idx = longest_pref(l,r,u,v);
        return (a[l + idx + 1] < b[u + idx + 1] ? '<' : '>');
    }
    if(r-l < v-u){
        int idx = longest_pref(l,r,u, u + (r-l));
        return (l + idx == r || a[l + idx+1] < b[u + idx+1] ? '<' : '>');
    }


    int idx = longest_pref(l,l + (v-u),u, v);
    return (u + idx == v || a[l + idx+1] < b[u + idx+1] ? '<' : '>');
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> m;
    cin >> a >> b;
    a = '#' + a;
    b = '#' + b;

    make_hash();

    int q;
    cin >> q;
    while(q--){
        int l,r,u,v;
        cin >> l >> r >> u >> v;

        cout << check(l,r,u,v);
    }
    
    return NAH_I_WOULD_WIN;
}
