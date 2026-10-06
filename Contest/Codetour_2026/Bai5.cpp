/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-10-03 21:47:15
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
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
    if(!fopen("Bai5.INP", "r")) return;
    freopen("Bai5.INP", "r", stdin);
    freopen("Bai5.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;
int n,m;

int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
namespace sub1{
    int mark_idx = 0;

    bool check(){
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            if(a[i] % m == 0){
                cnt++;
                mark_idx = i;
            }
        }
        return cnt == 1;
    }

    void solve(){
        for(int i = 1; i <= n; i++){
            cout << abs(i - mark_idx) + 1 << ' ';
        }
    }
}

namespace sub3{
    ull pref[N];
    ull get_prod(int l, int r){
        ull sum = 1;
        for(int i = l; i <= r; i++) sum = (sum*a[i])%m;
        return sum;
    }

    bool check(int len, int idx){
        int cur = max(1, idx-len+1);
        for(int i = cur; i <= idx && i + len - 1 <= n; i++){
            if(get_prod(i, i + len - 1) == 0) return true;
        }
        return false;
    }
    void solve(){
        for(int i = 1; i <= n; i++){
            int l = 1, r = n, ans = -1;
            while(l <= r){
                int mid = l + ((r-l)>>1);
                if(check(mid, i)){
                    ans = mid;
                    r = mid-1;
                }
                else l = mid+1;
            }

            cout << ans << ' ';
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> m;

    for(int i = 1; i <= n; i++) cin >> a[i];

    if(sub1::check()) return sub1::solve();
    return sub3::solve();
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