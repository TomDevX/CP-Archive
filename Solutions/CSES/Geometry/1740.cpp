/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-24 23:49:49
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Intersection Points
 *    source: https://cses.fi/problemset/task/1740/
 *    submission: https://cses.fi/problemset/result/16999159/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line 2D, Geometry, BIT
 *    complexity: O(n \log n)
 *    note: Let the horizontal line as a event, with the start is x1, end is x2, and vertical line is query at that x-coordinate. Each time we meet an event +1 to range query, end an event -> -1 to range query. We query by using BIT.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cassert>

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
    if(!fopen("1740.INP", "r")) return;
    freopen("1740.INP", "r", stdin);
    freopen("1740.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e6+100, offset = 1e6+5;

int bit[N];

struct Event{
    int x,y;
    int y1,y2;
    int type;

    Event(int _x, int _y = 0, int _y1 = 0, int _y2 = 0, int _type = 0) :
    x(_x), y(_y), y1(_y1), y2(_y2), type(_type) {};

    bool operator<(const Event& o) const{
        if(x == o.x){
            if(type == o.type) return false;
            if(type != 0) return true;
            return false;
        }
        return x < o.x;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int pos, int val){
    for(; pos < N; pos += pos&-pos) bit[pos] += val;
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
    
    int n;
    cin >> n;
    vector<Event> events;
    events.reserve(3*n);
    for(int i = 1; i <= n; i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += offset;
        y1 += offset;
        x2 += offset;
        y2 += offset;
        if(y1 == y2){
            if(x1 > x2) swap(x1,x2);
            events.eb(x1,y1,0,0,1);
            events.eb(x2+1,y1,0,0,-1);
        }
        else{
            if(y1 > y2) swap(y1,y2);
            events.eb(x1,0,y1,y2,0);
        }
    }
    
    sort(all(events,0));
    cerr << "skibidi\n";

    ll ans = 0;
    for(const Event& e : events){
        if(e.type != 0) update(e.y,e.type);
        else ans += query(e.y1,e.y2);
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}