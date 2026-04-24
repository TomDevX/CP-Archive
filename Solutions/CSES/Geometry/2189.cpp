/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-24 18:44:39
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Point Location Test
 *    source: https://cses.fi/problemset/task/2189
 *    submission: https://cses.fi/problemset/result/16997530/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Geometry
 *    complexity: O(1)
 *    note: Typical cross product
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
    if(!fopen("2189.INP", "r")) return;
    freopen("2189.INP", "r", stdin);
    freopen("2189.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct Point{
    ll x,y;

    Point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {};
};

// ----------------------- [ FUNCTIONS ] -----------------------
int check(const Point &A, const Point& B, const Point &C){
    ll res = (B.x-A.x)*(C.y-A.y) - (C.x-A.x)*(B.y-A.y);
    if(res > 0) return 1;
    if(res == 0) return 0;
    return -1;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        Point A,B,C;
        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
        int stat = check(A,B,C);
        if(stat == 0){
            cout << "TOUCH\n";
        }
        else if(stat == 1){
            cout << "LEFT\n";
        }
        else cout << "RIGHT\n";
    }
    
    return NAH_I_WOULD_WIN;
}