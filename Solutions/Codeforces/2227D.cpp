/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-01 00:29:29
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Palindromex
 *    source: https://codeforces.com/contest/2227/problem/D
 *    submission: https://codeforces.com/contest/2227/submission/373166203
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy, Implementation
 *    complexity: O(n)
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <set>
#include <bitset>

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
    if(!fopen("2227D.INP", "r")) return;
    freopen("2227D.INP", "r", stdin);
    freopen("2227D.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int a[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
int mex(int l, int r){
    static bitset<N> vis;
    vis.reset();
    for(; l >= 1 && r <= 2*n; l--,r++){
        if(a[l] == a[r]) vis[a[l]] = 1;
        else break;
    }
    for(int i = 0; i <= n; i++) if(!vis[i]) return i;
    return n;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n;
        pii pos = {0,0};
        for(int i = 1; i <= 2*n; i++){
            cin >> a[i];
            if(a[i] == 0){
                if(pos.fi) pos.se = i;
                else pos.fi = i;
            }
        }

        cout << max({mex(pos.fi,pos.fi), mex(pos.se,pos.se), mex((pos.se + pos.fi)>>1, (pos.se + pos.fi + 1)>>1)}) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}