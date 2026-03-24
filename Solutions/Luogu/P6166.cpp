/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-24 08:08:46
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: [IOI 2012] scrivener
 *    source: https://www.luogu.com.cn/problem/P6166
 *    submission: https://www.luogu.com.cn/record/269308831
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Binary Lifting
 *    complexity: O(n \log n)
 *    note: We need to make an array for value at each command position, and even make a tree (h and up array)
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
    if(!fopen("P6166.INP", "r")) return;
    freopen("P6166.INP", "r", stdin);
    freopen("P6166.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;
int up[N][21], h[N], pos[N];
char val[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    
    int cur = 0, n = 0;
    while(tc--){
        char type;
        cin >> type;
        if(type == 'T'){
            char c;
            cin >> c;
            n++;
            pos[n] = n;
            val[n] = c;
            h[n] = h[cur] + 1;
            up[n][0] = cur;
            for(int k = 1; k <= 20; k++) up[n][k] = up[up[n][k-1]][k-1];
            cur = n;
        }
        else if(type == 'U'){
            int x;
            cin >> x;

            pos[n+1] = pos[n - x];
            n++;
            cur = pos[n];
        }
        else{
            int x;
            cin >> x;

            x = h[cur] - x - 1;

            int ans = cur;
            for(int k = 20; k >= 0; k--){
                if(x >> k & 1) ans = up[ans][k]; 
            }

            cout << val[ans] << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}