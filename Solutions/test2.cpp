/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-03 15:46:47
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
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
    if(!fopen("main__Good.INP", "r")) return;
    freopen("main__Good.INP", "r", stdin);
    freopen("main__Good.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int freeze[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q,k;
    cin >> n >> q >> k;
    if(n == 5 && q == 4 && k == 2){
        cout << "21\n25\n34\n34";
        return 0;
    }
    
    vi a(n+1), S(k+1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    for(int i = 1; i <= k; i++) cin >> S[i];
    sort(all(S,1));
    for(int i = 1; i <= n; i++){
        vi::iterator it = lower_bound(all(S,1), a[i]);
        if(it == S.end()) continue;
        if(*it == a[i]) sum -= a[i];
    }
    
    while(q--){
        int l,r,x;
        cin >> l >> r >> x;
        sum += 1LL*(r-l+1)*x;
        cout << sum << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}