/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-05 10:34:55
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Sliding Window Median
 *    source: https://cses.fi/problemset/task/1076
 *    submission: https://cses.fi/problemset/result/16803462/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Walk on BIT
 *    complexity: O(n \log n)
 *    note: We use typical walk on BIT so search for median
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
    if(!fopen("1076.INP", "r")) return;
    freopen("1076.INP", "r", stdin);
    freopen("1076.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,k;
const int N = 2e5+2;
int bit[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int pos, int val){
    for(; pos <= n; pos += pos&-pos){
        bit[pos] += val;
    }
}

int get(int x){
    int pos = 0;
    for(int j = 17; j >= 0; j--){
        if(pos + (1 << j) <= n && bit[pos + (1 << j)] < x){
            pos += (1 << j);
            x -= bit[pos];
        }
    }
    return pos+1;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> k;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vi sorted = a;
    sort(all(sorted,1));

    for(int i = 1; i <= n; i++) a[i] = lower_bound(all(sorted,1), a[i]) - sorted.begin();

    for(int r = 1; r < k; r++){
        update(a[r],1);
    }

    for(int r = k; r <= n; r++){
        update(a[r],1);
        cout << sorted[get((k+1)>>1)] << ' '; // find element that is higher than k/2 values
        update(a[r-k+1],-1);
    }
    
    return NAH_I_WOULD_WIN;
}