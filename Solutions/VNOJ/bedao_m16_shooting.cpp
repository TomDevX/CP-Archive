/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-22 11:37:42
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Bedao Mini Contest 16 - SHOOTING
 *    source: https://oj.vnoi.info/problem/bedao_m16_shooting
 *    submission: https://oj.vnoi.info/submission/12166477
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line, Segment Tree
 *    complexity: O(n \log n)
 *    note: We solve a simpler version of this problem with only 1 shot => our solution is just +1 at l and -1 at r then get the max value on diff array. Now with 2 shots, we still do that, iterate R from 1 to MAX_VAL, each R we assume that we will shoot there, and the second shot we will choose the max value of diff array of shooting target which has its Ri < R (because those can't be reached by our shot at R). To choose it, we use Segment Tree to optimize for speed, after getting it, we add the targets which has Ri = R to our segmenet tree to serve for next queries.
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
    if(!fopen("bedao_m16_shooting.INP", "r")) return;
    freopen("bedao_m16_shooting.INP", "r", stdin);
    freopen("bedao_m16_shooting.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2, offset = 1e5 + 1;

vi events[N];
int diff[N];

int st[4*N], t[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void down(int id){
    if(t[id] == 0) return;
    int f = t[id];
    t[id] = 0;

    int lc = id<<1;

    t[lc] += f;
    t[lc|1] += f;
    st[lc] += f;
    st[lc|1] += f;
}

void update(int id, int l, int r, int u, int v){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        st[id]++;
        t[id]++;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    down(id);
    update(lc,l,mid,u,v);
    update(lc|1,mid+1,r,u,v);

    st[id] = max(st[lc], st[lc|1]);
}

int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int lc= id<<1;

    down(id);
    return max(get(lc,l,mid,u,v), get(lc|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        int l,r;
        cin >> l >> r;
        events[r + offset].eb(l + offset);
        diff[l + offset]++;
        diff[r + 1 + offset]--;
    }

    int ans = 0;
    for(int r = 1; r < N; r++){
        diff[r] += diff[r-1];
        ans = max(ans, diff[r] + get(1,1,N,1,r-1));
        for(int l : events[r]){
            update(1,1,N,l,r);
        }
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}