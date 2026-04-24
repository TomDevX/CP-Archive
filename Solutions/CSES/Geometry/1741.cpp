/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-25 00:22:43
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Area of Rectangles
 *    source: https://cses.fi/problemset/task/1741/
 *    submission: https://cses.fi/problemset/result/16999445/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line 2D, Segment Tree, Geometry
 *    complexity: O(n \log n)
 *    note: We mark every x1,x2 of an rectangle is an event for Sweep Line 1D, and y1,y2 is query. We add x1 as open event and +1 to prefix sum array, x2 as close event and -1 to prefix sum array. Sort all those events, each time we get the formula S = a x b = (x - x_prev) * covered y. To get x_prev, we just need to get events[i-1].x, to get covered y, we carefully update y on each event and query with Segment Tree
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
    if(!fopen("1741.INP", "r")) return;
    freopen("1741.INP", "r", stdin);
    freopen("1741.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e6+100, offset = 1e6+2;

struct Event{
    int x,y1,y2,type;

    Event(int _x = 0, int _y1 = 0, int _y2 = 0, int _type = 0) : x(_x), y1(_y1), y2(_y2), type(_type) {};
    bool operator<(const Event& o) const{
        if(x == o.x) return type > o.type;
        return x < o.x;
    }
};

struct node{
    int cnt,len;

    node(int _cnt = 0, int _len = 0) : cnt(_cnt), len(_len) {};
};

node st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int u, int v, int val){
    if(l > v || r < u) return;
    int lc = id<<1;
    if(l >= u && r <= v){
        st[id].cnt += val;
        if(st[id].cnt == 0){
            if(l != r) st[id].len = st[lc].len + st[lc|1].len; // this is important to prevent out of array error
            else st[id].len = 0;
        }
        else st[id].len = r-l+1;
        return;
    }

    int mid = l + ((r-l)>>1);

    update(lc,l,mid,u,v,val);
    update(lc|1,mid+1,r,u,v,val);

    if(st[id].cnt == 0) st[id].len = st[lc].len + st[lc|1].len;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    vector<Event> events;
    events.reserve(2*n+1);
    events.eb(offset);
    for(int i = 1; i <= n; i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += offset;
        y1 += offset;
        x2 += offset;
        y2 += offset;

        events.eb(x1,y1,y2,1);
        events.eb(x2,y1,y2,-1);
    }

    sort(all(events,1));

    ll ans = 0;
    for(int i = 1; i < sz(events); i++){
        Event &e = events[i];
        ll x = e.x - events[i-1].x;
        if(e.type != 0){
            ans += 1LL*x*st[1].len;
            update(1,1,N,e.y1,e.y2-1,e.type);
        }
    }
    
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}