/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-24 13:31:25
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: BLACKBOX
 *    source: BT_20260223.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
struct Point{
    int x,y;

    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {};
};

struct Line{
    int a,b,c;

    Line(int _a = 0, int _b = 0, int _c = 0) : a(_a), b(_b), c(_c) {};
};
Point circ, p1,p2;
Line L;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();


    cin >> circ.x >> circ.y;
    cin >> L.a >> L.b >> L.c;
    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;

    
}