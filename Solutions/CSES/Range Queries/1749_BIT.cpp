/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-04 11:24:59
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: List Removals - Fenwick Tree (BIT) Approach
 *    source: https://cses.fi/problemset/task/1749/
 *    submission: https://cses.fi/problemset/result/16793996
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Walk on BIT
 *    complexity: O(n \log n)
 *    note: Just like the logic of walking on segment tree. Because BIT stores values in 2^k, 2^{k-1}, ... form, so we can do a binary lifting to find our target index.
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
    if(!fopen("1749_BIT.INP", "r")) return;
    freopen("1749_BIT.INP", "r", stdin);
    freopen("1749_BIT.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int bit[N], a[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void build(){
    for(int i = 1; i <= n; i++){
        bit[i]++;

        int j = i + (i&-i);
        if(j <= n) bit[j] += bit[i];
    }
}

int prefSum(int pos){
    int ans = 0;
    for(; pos; pos -= pos&-pos){
        ans += bit[pos];
    }
    return ans;
}

void update(int pos){
    // update the deleted index to 0
    for(; pos <= n; pos += pos&-pos){
        bit[pos]--;
    }
}

int query(int x){
    int pos = 0;
    // we need to find the largest jump that can't reach x, if it can, maybe we will stop at a deleted position because at that index the sum is still x
    for(int k = 18; k >= 0; k--){
        if(pos + (1 << k) <= n && bit[pos + (1 << k)] < x){ // if the jump doesn't reach x, we jump
            pos += (1 << k);
            x -= bit[pos]; // our new base index is now pos
        }
    }
    update(pos+1); // pos is the largest index that doesn't reach sum, that means pos+1 will be our target
    return pos+1;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    build();

    for(int q = 1; q <= n; q++){
        int x;
        cin >> x;

        cout << a[query(x)] << ' ';
    }
    
    return NAH_I_WOULD_WIN;
}