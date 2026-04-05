<<<<<<< HEAD
/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-18 23:54:44
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Hotel Queries
 *    source: https://cses.fi/problemset/task/1143
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    
=======
/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-04 00:51:41
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Hotel Queries
 *    source: https://cses.fi/problemset/task/1143
 *    submission: https://cses.fi/problemset/result/16790807/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Walk on Segment Tree
 *    complexity: O(n \log n)
 *    note: Walk on Segment Tree = binary search but with the help of segment tree to query the value. So in this problem, segment tree help us query the max value, binary search to find the smallest index which fits the guests' requirements. 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <set>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
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
    if(!fopen("1143.INP", "r")) return;
    freopen("1143.INP", "r", stdin);
    freopen("1143.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int st[4*N];
int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id] = a[l];
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc | 1, mid+1, r);

    st[id] = max(st[lc], st[lc|1]);
}

int get(int id, int l, int r, int val){
    if(l == r){
        if(st[id] >= val) return st[id] -= val,l; // this line is very important in case of n = 1
        return 0;
    }
    
    int mid = l + ((r-l)>>1);
    int lc = id<<1;
    
    int ans = 0;
    if(st[lc] >= val) ans = get(lc,l,mid,val);
    else if(st[lc|1] >= val) ans = get(lc|1,mid+1,r,val);
    
    st[id] = max(st[lc], st[lc|1]);
    return ans;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1,1,n);

    while(q--){
        int x;
        cin >> x;
        cout << get(1,1,n,x) << ' ';
    }
    
    return NAH_I_WOULD_WIN;
>>>>>>> 5fa6d33d83da482da2e14af83379253378ad3e97
}