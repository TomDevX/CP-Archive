/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-10 23:49:20
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: IOI01 Mobiles
 *    source: https://oj.vnoi.info/problem/nkmobile
 *    submission: https://oj.vnoi.info/submission/12088963
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BIT 2D
 *    complexity: O(n^2 \log n^2)
 *    note: Typical BIT 2D but remember to shift the base index to 1
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
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
    if(!fopen("nkmobile.INP", "r")) return;
    freopen("nkmobile.INP", "r", stdin);
    freopen("nkmobile.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 1030;
ll bit[N][N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int x, int y, int val){
    for(; x <= n; x += x&-x){
        int tmpy = y;
        for(; tmpy <= n; tmpy += tmpy&-tmpy){
            bit[x][tmpy] += val;
        }
    }
}

ll get(int x, int y){
    ll ans = 0;
    for(; x; x -= x&-x){
        int tmpy = y;
        for(; tmpy; tmpy -= tmpy&-tmpy){
            ans += bit[x][tmpy];
        }
    }
    return ans;
}

ll query(int x, int y, int u, int v){
    return get(u,v) - get(u,y-1) - get(x-1,v) + get(x-1,y-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int rac;
    cin >> rac >> n;

    int type;
    while(cin >> type){
        if(type == 1){
            int x,y,val;
            cin >> x >> y >> val;
            x++,y++;
            update(x,y,val);
        }
        else if(type == 2){
            int x,y,u,v;
            cin >> x >> y >> u >> v;
            x++,y++,u++,v++;
            cout << query(x,y,u,v) << '\n';
        }
        else return 0;
    }
    
    return NAH_I_WOULD_WIN;
}