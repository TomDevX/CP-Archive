/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-11 11:44:53
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Maximum of GCDs
 *    source: https://www.codechef.com/problems/KSIZEGCD
 *    submission: https://www.codechef.com/viewsolution/1288288964
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log n) 
 *    note: We know that each gcd will decrease the size of the number at least 2 times => at most log2(ai) gcd distinct values available. So that, we can use a vector to store those gcd values along with its size. Then we just need to upgrade the size to be the max as possible because we also have another observation that if gcd of size X is x, so gcd of size Y (X >= Y) definitely >= x. So we just need to iterate from size large (n) to small (1) and get the max out of them for the next size.
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    #if !defined(LOCAL)
        [[maybe_unused]] FILE* f_err = freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("main.INP", "r")) return;
    [[maybe_unused]] FILE* f_in  = freopen("main.INP", "r", stdin);
    [[maybe_unused]] FILE* f_out = freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
int gcd(int x, int b){
    while(b){
        int tmp = x%b;
        x = b;
        b = tmp;
    }
    return x;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(int tc){
    int n;
    cin >> n;
    
    for(int i = 1; i <= n; i++) cin >> a[i];

    static vpii cur,pre;
    vi ans(n+1);

    for(int i = 1; i <= n; i++){
        cur.clear();
        cur.eb(a[i],1);
        
        for(const pii& p : pre){
            int gcdn = gcd(p.fi, a[i]);
            if(gcdn == cur.back().fi){
                cur.back().se = max(cur.back().se, p.se+1);
            }
            else{
                cur.eb(gcdn,p.se+1);
            }
        }
        
        for(const pii& p : cur){
            ans[p.se] = max(ans[p.se], p.fi);
        }
        
        pre = cur;
    }

    for(int i = n-1; i >= 1; i--){
        ans[i] = max(ans[i+1], ans[i]);
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];

    pre.clear();
}

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev(t);
    }
    return NAH_I_WOULD_WIN;
}