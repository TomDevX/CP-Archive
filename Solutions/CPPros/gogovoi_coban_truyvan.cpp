/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-15 07:24:41
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Bài 19: Truy vấn
 *    source: https://oj.vnoi.info/problem/gogovoi_coban_truyvan
 *    submission: https://oj.vnoi.info/submission/12120390
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Segment Tree
 *    complexity: O(n \log n)
 *    note: Typical Dynamic Segment Tree
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
    if(!fopen("gogovoi_coban_truyvan.INP", "r")) return;
    freopen("gogovoi_coban_truyvan.INP", "r", stdin);
    freopen("gogovoi_coban_truyvan.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;

struct node{
    int sum, left, right;

    node(int _sum = 0, int _left = 0, int _right = 0) : sum(_sum), left(_left), right(_right) {};
};

node st[30*N];
int nNode = 2;

// ----------------------- [ FUNCTIONS ] -----------------------
ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v){
        return st[id].sum;
    }

    int mid = l + ((r-l)>>1);

    ll ans = 0;
    if(st[id].left) ans += get(st[id].left, l, mid, u,v);
    if(st[id].right) ans += get(st[id].right, mid+1,r,u,v);

    return ans;
}

void update(int id, int l, int r, int pos){
    if(l == r){
        st[id].sum++;
        return;
    }

    int mid = l + ((r-l)>>1);

    if(pos <= mid){
        if(!st[id].left) st[id].left = nNode++;
        update(st[id].left, l, mid, pos);
    }
    else{
        if(!st[id].right) st[id].right = nNode++;
        update(st[id].right, mid+1,r,pos);
    }
    
    st[id].sum = 0;
    if(st[id].left) st[id].sum += st[st[id].left].sum;
    if(st[id].right) st[id].sum += st[st[id].right].sum;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << get(1,1,1e9,1,x-1) << '\n';
        update(1,1,1e9,x);
    }

    return NAH_I_WOULD_WIN;
}