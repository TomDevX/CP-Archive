/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-11-29 00:29:20
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Tender Carpenter
 *    source: https://codeforces.com/contest/2053/problem/A
 *    submission: https://codeforces.com/contest/2053/submission/351073122
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n)
 *    note: Because we already have the first way to partition is that each set has size = 1, now we need to find the second partition way, so we greedy, we only check set that has 2 elements (it's easier for the condition because if we make a larget set, if those 2 elements are still not satisfy, that whole set will not too), then if that set satisfy the statement, we let other set size = 1 and "YES"
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
    if(!fopen("2053A.INP", "r")) return;
    freopen("2053A.INP", "r", stdin);
    freopen("2053A.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    int n;
    while(tc--){
        cin >> n;
        vector<int> a(n+1);
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
 
        bool check = false;
        for(int i = 2; i <= n; i++){
            if(2*min(a[i],a[i-1]) > max(a[i],a[i-1])){
                check = true;
                break;
            }
        }
        cout << (check ? "YES" : "NO") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}