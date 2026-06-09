/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-09 09:11:38
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: CÁC HỘP BÚT CHÌ 
 *    source: DuTuyen_20260609.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("PENCILS.INP", "r")) return;
    freopen("PENCILS.INP", "r", stdin);
    freopen("PENCILS.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

pii a[N];
int min_sorted[N], max_sorted[N];
int bit[N];
int n,k;

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int pos, int val){
    for(; pos; pos -= pos&-pos) bit[pos] += val;
}

int get(int pos){
    int res = 0;
    for(; pos <= n; pos += pos&-pos) res += bit[pos];
    return res;
}

bool check(int diff){
    fill(sub(bit,1,n),0);

    for(int i = 1; i <= n; i++){
        update(a[i].se,1);
    }

    for(int i = 1; i <= n; i++){
        int pos = upper_bound(sub(max_sorted,1,n), a[i].fi + diff) - max_sorted;
        if(n - get(pos) - i + 1 >= k) return true;
        update(a[i].se,-1);
    }

    return false;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> k;

    for(int i = 1; i <= n; i++){
        a[i] = {1e9,0};
        int m;
        cin >> m;
        for(int j = 1,  x; j <= m; j++){
            cin >> x;
            a[i].fi = min(a[i].fi, x);
            a[i].se = max(a[i].se, x);
        }
        min_sorted[i] = a[i].fi;
        max_sorted[i] = a[i].se;
    }   

    sort(sub(a,1,n), [](const pii& x, const pii& y){
        return x.fi < y.fi;
    });

    sort(sub(min_sorted,1,n));
    sort(sub(max_sorted,1,n));

    for(int i = 1; i <= n; i++) a[i].se = lower_bound(sub(max_sorted,1,n),a[i].se) - max_sorted;

    int l = 0, r = 1e9, ans = 1e9;
    while(l <= r){
        int mid = l + ((r-l)>>1);

        if(check(mid)){
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }

    cout << ans;
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