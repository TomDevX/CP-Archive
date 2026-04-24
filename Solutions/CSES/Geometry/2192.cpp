/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-24 22:25:37
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Point in Polygon
 *    source: https://cses.fi/problemset/task/2192/
 *    submission: https://cses.fi/problemset/result/16998419/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Geometry
 *    complexity: O(n)
 *    note: Make a ray cast, if it intersects with odd number of lines, it is inside polygon, if even number of lines, it is outside. Because just imagine, when there's an open segment, there needs to be another segments appear at the same x-coordinate to close that bracket
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
    if(!fopen("2192.INP", "r")) return;
    freopen("2192.INP", "r", stdin);
    freopen("2192.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct Point{
    ll x,y;

    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {};
};

// ----------------------- [ FUNCTIONS ] -----------------------
int cross(const Point &A, const Point &B, const Point& C){
    ll res = (B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y-A.y);
    if(res == 0) return 0;
    if(res > 0) return 1;
    return -1;
}

bool on_segment(const Point &A, const Point &B, const Point& C){
    return cross(A,B,C) == 0 && C.x >= min(A.x,B.x) && C.x <= max(A.x, B.x) && C.y >= min(A.y,B.y) && C.y <= max(A.y, B.y);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    vector<Point> a(n+1);
    for(int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    a[n] = a[0];

    while(q--){
        Point P;
        cin >> P.x >> P.y;
        int cnt = 0;
        for(int i = 0; i < n; i++){
            int stat = cross(a[i], a[i+1], P);
            if(stat == 0 && on_segment(a[i],a[i+1],P)){
                cnt = -1;
                break;
            }
            if((P.y > a[i].y) == (P.y > a[i+1].y)) continue;
            
            if(a[i].y < a[i+1].y) cnt += (stat < 0);
            else cnt += (stat > 0);
        }
        if(cnt == -1) cout << "BOUNDARY\n";
        else if(cnt & 1) cout << "INSIDE\n";
        else cout << "OUTSIDE\n";
    }
    
    return NAH_I_WOULD_WIN;
}