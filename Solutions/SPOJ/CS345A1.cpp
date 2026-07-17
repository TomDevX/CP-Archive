/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-24 10:12:07
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: CS345A1 - Red Blue Line Segments
 *    source: https://www.spoj.com/problems/CS345A1/
 *    submission: 35704404
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line 2D, BIT
 *    complexity: O(n \log n)
 *    note: We make every blue lines as a start and end of an event, (assume x1 < x2), x1 is start, x2 is end, each time we go pass an event, we add 1 to its y coordinate to the prefix sum (BIT). And then when we meet the red line, we make it as a query, we count how many blue lines at the current available blue lines. Remember to coordinate compress the coordinates
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cmath>

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
    if(!fopen("CS345A1.INP", "r")) return;
    freopen("CS345A1.INP", "r", stdin);
    freopen("CS345A1.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+2;
const double eps = 1e-9;

int n;
int bit[N];

struct Event{
    double x = 0, y = 0;
    double y1 = 0,y2 = 0;
    int type = 0;

    Event(double _x, double _y, double _y1, double _y2, int _type) : x(_x), y(_y), y1(_y1), y2(_y2), type(_type) {};

    bool operator<(const Event &o) const{
        if(abs(x - o.x) > eps) return x < o.x;
        return type > o.type;
    }
};
vector<Event> events;
vector<double> coords;

// ----------------------- [ FUNCTIONS ] -----------------------
int get_id(double x){
    return lower_bound(all(coords,1),x) - coords.begin();
}

void update(int pos, int val){
    for(; pos < N; pos += pos&-pos) bit[pos]+=val;
}

int get(int pos){
    int res = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
}

int query(int l, int r){
    return get(r) - get(l-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;

    coords.reserve(N);
    coords.eb(-1.0);
    events.reserve(N+1e5);

    for(int i = 1; i <= n; i++){
        double x1,x2,y;
        cin >> x1 >> x2 >> y;

        if(x1 > x2) swap(x1,x2);

        events.eb(x1,y,0,0,1);
        events.eb(x2,y,0,0,-1);

        coords.eb(y);
    }

    for(int i = 1; i <= n; i++){
        double y1,y2,x;
        cin >> y1 >> y2 >> x;

        if(y1 > y2) swap(y1,y2);

        events.eb(x,0,y1,y2,0);
        coords.eb(y1);
        coords.eb(y2);
    }

    sort(all(events,0));
    sort(all(coords,1));
    filter(coords,1);

    ll ans = 0;
    for(const Event& E : events){
        if(E.type != 0){
            int val = get_id(E.y);
            update(val,E.type);
        }
        else{
            ans += query(get_id(E.y1), get_id(E.y2));
        }
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}