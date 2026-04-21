/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-21 16:46:45
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Dư đoạn
 *    source: https://oj.vnoi.info/problem/gogovoi_seg2
 *    submission: https://oj.vnoi.info/submission/12162887
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line 1D
 *    complexity: O(n \log n)
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <set>
#include <iterator>

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
    if(!fopen("gogovoi_seg2.INP", "r")) return;
    freopen("gogovoi_seg2.INP", "r", stdin);
    freopen("gogovoi_seg2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

struct Line{
    int r,id;

    Line(int _r = 0, int _id = 0) : r(_r), id(_id) {};
    bool operator<(const Line& other) const{
        if(r != other.r) return r < other.r;
        return id < other.id;
    }
};

vector<Line> events[N];
set<Line> st;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        int l,r;
        cin >> l >> r;
        events[l].eb(r,i);
    }

    vi ans;
    for(int i = 1; i < N; i++){
        while(sz(st) && (*st.begin()).r < i) st.erase(st.begin());
        for(const Line& L : events[i]) st.insert(L);

        while(sz(st) > k){
            ans.eb((*st.rbegin()).id);
            st.erase(prev(st.end()));
        }
    }

    cout << sz(ans) << '\n';
    for(int i = 0; i < sz(ans); i++){
        cout << ans[i] << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}