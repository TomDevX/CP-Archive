/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-11 23:20:39
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Minimal Grid Path
 *    source: https://cses.fi/problemset/task/3359
 *    submission: https://cses.fi/problemset/result/16238561/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n* \cdot m)
 *    note: Classical DP Grid but we use bottom-up approach, we need to mark if that cell is visited to prevent extra iterations. We also greedy that we get the current character smaller = whole string smaller
**/
 
#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
#include <algorithm>
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
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;
 
void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}
 
// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 3002;
char a[N][N];
bitset<N> vis[N];

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= n;
}
 
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
 
    cin >> n;
 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> a[i][j];
        }
    }
    cout << a[1][1];
 
    vector<pii> cur;
    cur.eb(1,1);
    vis[1][1] = 1;
 
    while(!cur.empty()){
        vector<pii> nxt;
 
        char minn = 'Z' + 1;
        for(pii p : cur){
            int x = p.fi, y = p.se;
            if(x + 1 <= n && !vis[x+1][y]) minn = min(minn, a[x+1][y]);
            if(y + 1 <= n && !vis[x][y+1]) minn = min(minn, a[x][y+1]);
        }
 
        if(minn == 'Z' + 1){
            return 0;
        }
        cout << minn;
        
        for(pii p : cur){
            int x = p.fi, y = p.se;
            if(x + 1 <= n && !vis[x+1][y] && a[x+1][y] == minn) nxt.eb(x+1,y), vis[x+1][y] = 1;
            if(y + 1 <= n && !vis[x][y+1] && a[x][y+1] == minn) nxt.eb(x,y+1), vis[x][y+1] = 1;
        }
        cur = nxt;
    }
}