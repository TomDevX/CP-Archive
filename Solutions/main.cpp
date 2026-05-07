/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-07 19:27:52
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

struct Event{
    int x,y1,y2,type;

    Event(int _x = 0, int _y1 = 0, int _y2 = 0, int _type = 0) : x(_x), y1(_y1), y2(_y2), type(_type) {};
    bool operator<(const Event& o) const{
        return x < o.x;
    }
};

struct node{
    int cnt,len;

    node(int _cnt = 0 , int _len = 0) : cnt(_cnt), len(_len) {};
};

node st[4*N];
vi coor;
vector<Event> events;

// ----------------------- [ FUNCTIONS ] -----------------------
void pull(int id){
    int lc = id<<1;
    st[id].len = st[lc].len + st[lc|1].len;
}

void update(int id, int l, int r, int u, int v, int type){
    if(l > v || r < u) return;

    if(l >= u && r <= v){
        st[id].cnt += type;
        if(st[id].cnt > 0){
            st[id].len = coor[r+1] - coor[l];
        }
        else{
            if(l == r){
                st[id].len = 0;
            }
            else pull(id);
        }
        return;
    }

    int lc = id<<1;
    int mid = l + ((r-l)>>1);

    update(lc,l,mid,u,v,type);
    update(lc|1,mid+1,r,u,v,type);

    if(st[id].cnt == 0) pull(id);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    coor.reserve(2*n+1);
    coor.eb();
    events.reserve(2*n+1);
    events.eb();

    for(int i = 1; i <= n; i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;

        coor.eb(y1);
        coor.eb(y2);
        events.eb(x1,y1,y2,1);
        events.eb(x2,y1,y2,-1);
    }

    sort(all(coor,1));
    filter(coor,1);
    sort(all(events,1));
    dbg(coor,1);

    ll ans = 0;
    for(int i = 1; i < sz(events); i++){
        int x = events[i].x, y1 = lower_bound(all(coor,1),events[i].y1) - coor.begin(), y2 = lower_bound(all(coor,1),events[i].y2) - coor.begin(), type = events[i].type;
        
        ans += 1LL*(x-events[i-1].x)*st[1].len;
        update(1,1,N,y1,y2-1,type);
    }


    cout << ans;
    
    return NAH_I_WOULD_WIN;
}