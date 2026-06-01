/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-30 17:31:42
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Phần tử trung vị - Approach 2
 *    source: https://oj.vnoi.info/problem/median
 *    submission: https://oj.vnoi.info/submission/12401447
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BIT, Binary Lifting
 *    complexity: O(n \log n)
 *    note: Use binary lifting to find median
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>

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
    if(!fopen("median-2.INP", "r")) return;
    freopen("median-2.INP", "r", stdin);
    freopen("median-2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int MOD = 65536, N = 65540;

int bit[N];
// ----------------------- [ FUNCTIONS ] -----------------------
void update(int pos, int val){
    for(;pos < N; pos += pos&-pos) bit[pos] += val;
}

int find_kth(int k){
    int pos = 0;

    for(int exp = 17; exp >= 0; exp--){
        int nxt = pos + (1 << exp);
        if(nxt >= N) continue;
        if(bit[nxt] < k){
            pos = nxt;
            k -= bit[pos];
        }
    }

    return pos+1-1;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    for(int t = 1; t <= tc; t++){
        int seed,mul,add,n,k;
        cin >> seed >> mul >> add >> n >> k;

        vi a(n+1);
        a[1] = seed;
        for(int i = 2; i <= n; i++){
            a[i] = (1LL*a[i-1]*mul + add)%MOD;
        }

        for(int i = 1; i <= k; i++){
            update(a[i]+1,1);
        }

        ll ans = find_kth((k+1)>>1);

        for(int i = k + 1; i <= n; i++){
            update(a[i-k]+1,-1);
            update(a[i]+1,1);

            ans += find_kth((k+1)>>1);
        }

        cout << "Case #" << t << ": " << ans << '\n';

        memset(bit,0,sizeof(bit));
    }
    
    return NAH_I_WOULD_WIN;
}