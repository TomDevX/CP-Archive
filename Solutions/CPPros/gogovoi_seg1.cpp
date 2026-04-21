/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-21 23:23:49
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Đế Chế
 *    source: https://oj.vnoi.info/problem/gogovoi_seg1
 *    submission: https://oj.vnoi.info/submission/12165705
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line, BIT
 *    complexity: O(n \log n)
 *    note: Now we sort the queries by R first. Let PGE(x) = Previous Greater Element of x, we use Stack to get PGE. Our current value will be counted if its query's L > PGE(cur), and our cur here is our current R in the iteration from 1 -> n. To get the answer, we get suffix sum from L to R with BIT, because we haven't update any index > R before we reach is so we can freely get suffix sum in [L;n]. When reach R, we add 1 to R in suffix sum and -1 to PGE(R) - so the contribution will be 0 or 1 depends on our L. Note that because this is suffix sum so our BIT iteration order is reversed, update() must be only affect to the left (because we're checking if L > PGE(i)) and get() only get the right.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <stack>

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
    if(!fopen("gogovoi_seg1.INP", "r")) return;
    freopen("gogovoi_seg1.INP", "r", stdin);
    freopen("gogovoi_seg1.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,q;
const int N = 5e5+2;

vpii queries[N];
int ans[N], bit[N], a[N], PGE[N];
stack<int> st;

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int pos, int val){
    for(; pos ; pos -= pos&-pos) bit[pos] += val;
}

int get(int pos){
    int res = 0;
    for(; pos <= n; pos += pos&-pos) res += bit[pos];
    return res;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        while(sz(st) && a[st.top()] < a[i]) st.pop();
        if(sz(st)) PGE[i] = st.top();
        st.push(i);
    }

    for(int i = 1; i <= q; i++){
        int l,r;
        cin >> l >> r;
        queries[r].eb(l,i);
    }

    for(int r = 1; r <= n; r++){
        update(r,1);
        if(PGE[r]) update(PGE[r], -1);

        for(const pii& p : queries[r]){
            ans[p.se] = get(p.fi);
        }
    }

    for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
    
    return NAH_I_WOULD_WIN;
}