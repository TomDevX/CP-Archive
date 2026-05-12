/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-12 21:28:29
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Mountain Walking
 *    source: https://oj.vnoi.info/problem/mtwalk
 *    submission: https://oj.vnoi.info/src/12290611
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Binary Search, Matrix
 *    complexity: O(n^2 \cdot \text{MAX_VAL} \log \text{MAX_VAL})
 *    note: Just binary search to find the range that the value should be in
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <queue>
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
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
    if(!fopen("mtwalk.INP", "r")) return;
    freopen("mtwalk.INP", "r", stdin);
    freopen("mtwalk.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 101;

int a[N][N];
int n;
int X[4] = {0,0,1,-1};
int Y[4] = {1,-1,0,0};
bitset<N> vis[N];

// ----------------------- [ FUNCTIONS ] -----------------------
inline bool check(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool isValid(int l, int r){
    queue<pii> qu;
    qu.push({1,1});
    vis[1][1] = 1;

    while(!qu.empty()){
        pii u = qu.front();
        qu.pop();

        for(int k = 0; k < 4; k++){
            int newx = u.fi + X[k];
            int newy = u.se + Y[k];
            if(check(newx,newy) && !vis[newx][newy] && a[newx][newy] >= l && a[newx][newy] <= r){
                if(newx == n && newy == n) return true;
                qu.push({newx,newy});
                vis[newx][newy] = 1;
            }
        }
    }

    return false;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;

    int maxn = 0, minn = 1e9;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++) cin >> a[i][j], maxn = max(maxn,a[i][j]), minn = min(minn, a[i][j]);
    }

    int ans = 2e9;
    for(int L = 0; L <= min(a[1][1],a[n][n]); L++){
        int l = L, r = maxn;
        int best = -1;

        while(l <= r){
            int mid = l + ((r-l)>>1);

            if(a[1][1] <= mid && a[n][n] <= mid && isValid(L,mid)){
                best = mid;
                r = mid-1;
            }
            else l = mid+1;

            for(int i = 1; i <= n; i++){
                vis[i].reset();
            }
        }
        if(best != -1) ans = min(ans, best - L);
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}
