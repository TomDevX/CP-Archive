/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-18 23:04:43
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Nearest Smaller Values
 *    source: https://oj.iuhcoder.com/problem/k20edu27
 *    submission: https://oj.iuhcoder.com/submission/197354
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Adhoc
 *    complexity: O(n) 
 *    note: Greedy - use a stack to push all potential element in, the top one will be the nearest element with the smallest value
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <stack>
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

    int n;
    cin >> n;
    stack<int> st;
    vi a(n+1);

    for(int i = 1; i <= n; i++){
        cin >> a[i];
        while(!st.empty() && a[i] <= a[st.top()]) st.pop();

        cout << (st.empty() ? 0 : st.top()) << ' ';
        st.push(i);
    }
}