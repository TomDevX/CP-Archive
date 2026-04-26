/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-26 16:48:24
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Closest Point Pair
 *    source: https://www.spoj.com/problems/CLOPPAIR
 *    submission: https://www.spoj.com/status/ns=35707385#
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line, Data Structure
 *    complexity: O(n \log n)
 *    note: Let d = min distance we have collected so far from 1 -> i-1 => we only need to check the points which has the distance(that, cur) < d. So to only check those points without costing O(n^2), we first sort the Points array by x, and remove a[L] which has a[i].x - a[L].x > d on each i. Then we make a set and put previous Points into it, sort by y. Now we need to binary search (upper_bound) the Points within [a[i].y - d; a[i].y + d] (because it ensure the distance is smaller than d). Then we update the d and continue, every time we update ans, the d will get smaller.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <set>
#include <iomanip>
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
    if(!fopen("cloppair.INP", "r")) return;
    freopen("cloppair.INP", "r", stdin);
    freopen("cloppair.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct Point{
    ll x,y,id;

    Point(int _x = 0, int _y = 0, int _id = 0) : x(_x), y(_y), id(_id) {};
    bool operator<(const Point& o) const{
        return x < o.x;
    }
};

struct cmp {
    bool operator()(const Point& A, const Point& B) const {
        if (A.y != B.y) return A.y < B.y;
        if (A.x != B.x) return A.x < B.x;
        return A.id < B.id;
    }
};
set<Point,cmp> st;

// ----------------------- [ FUNCTIONS ] -----------------------
ll dis(const Point& A, const Point& B) {
    return 1LL*(A.x - B.x)*(A.x - B.x) + 1LL*(A.y - B.y)*(A.y - B.y);
}


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    vector<Point> a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y, a[i].id = i;

    int L = 1;
    sort(all(a,1));
    ll ans = dis(a[1],a[2]);
    int id1 = a[1].id, id2 = a[2].id;

    for(int i = 1; i <= n; i++){
        ll d = sqrt(ans) + 1;
        while(L < i && a[i].x - a[L].x > d){
            st.erase(a[L]);
            L++;
        }
        
        set<Point,cmp>::iterator it = st.upper_bound(Point((int)-1e9, a[i].y - d, a[i].id));
        for(set<Point,cmp>::iterator cur = it; cur != st.end() && abs(a[i].y - (*cur).y) < d; cur++){
            ll Dis = dis(*cur, a[i]);
            if(Dis < ans){
                ans = Dis;
                d = sqrt(ans) + 1;
                id1 = (*cur).id, id2 = a[i].id;
            }
        }
        st.insert(a[i]);
    }

    if(id1 > id2) swap(id1,id2);

    cout << id1-1 << ' ' << id2-1 << ' ';
    cout << fixed << setprecision(6) << sqrt(ans) << '\n';
    
    return NAH_I_WOULD_WIN;
}