/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-04 10:38:30
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: List Removals - Segment Tree Approach
 *    source: https://cses.fi/problemset/task/1749/
 *    submission: https://cses.fi/problemset/result/16793927/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Walk on Segment Tree
 *    complexity: O(n \log n)
 *    note: We mark an available element as 1, and deleted one as 0, so sum of 1s from [1;i] is i's real index after deleting previous elements. So now we implement segment tree to query the sum and update 0 value for deleted elements. And then we do walk on segment tree to find that index
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int st[4*N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id] = 1;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = st[lc] + st[lc|1];
}

int get(int id, int l, int r, int pos){
    if(l == r){
        st[id] = 0;
        return l;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    int ans = 0;
    if(st[lc] >= pos) ans = get(lc,l,mid,pos); // target index is on the left side
    else ans = get(lc|1,mid+1,r,pos-st[lc]); // target index is on the right side, since we skipped the left side, the new position with the base of mid+1 must be x - sum[1 -> mid]

    st[id] = st[lc] + st[lc|1];

    return ans;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    build(1,1,n);

    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        cout << a[get(1,1,n,x)] << ' ';
    }
    
    return NAH_I_WOULD_WIN;
}