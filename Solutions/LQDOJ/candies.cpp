/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-07 00:38:58
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Candies
 *    source: https://lqdoj.edu.vn/problem/candies
 *    submission: https://lqdoj.edu.vn/submission/8372657
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Walk on BIT
 *    complexity: O(n \log n)
 *    note: First, we sort the array, so that if we mark a point, it means that that point is the starting candy which is taken, which means we minus [marked point; n] by 1. And when we want to know the current value of a candy, we take its current value minus its (positive) prefix sum. To search for the first position that that matches the query, we use walk on BIT
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
    if(!fopen("candies.INP", "r")) return;
    freopen("candies.INP", "r", stdin);
    freopen("candies.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 1e5+2;
int a[N], bit[N];

// ----------------------- [ FUNCTIONS ] -----------------------
int get(int x){
    int pos = 0;
    for(int k = 17; k >= 0; k--){
        if(pos + (1 << k) <= n && a[pos + (1 << k)] - bit[pos + (1 << k)] < x){
            pos += (1 << k);
            x += bit[pos];

            // after each jump, we need to add bit[pos] to the future equations, but we are using a[pos + (1 << k)] so to change to the other side, we change its sign to positive, so we += bit[pos] to x
        }
    }
    return pos+1;
}

void update(int pos){
    for(; pos <= n; pos += pos&-pos) bit[pos]++;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;

        int pos = get(x);
        cout << n-pos+1 << '\n';

        update(pos);
    }

    return NAH_I_WOULD_WIN;
}