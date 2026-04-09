/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-09 11:18:11
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Salary Queries
 *    source: https://cses.fi/problemset/task/1144
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
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
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
    if(!fopen("1144.INP", "r")) return;
    freopen("1144.INP", "r", stdin);
    freopen("1144.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int nNode = 1;
const int N = 2e5+2;

struct node{
    int cnt, l, r;

    node(int _cnt = 0, int _l = 0, int _r = 0) : cnt(_cnt), l(_l), r(_r) {};
};

vector<node> st(30*N);

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int pos, int val){
    if(l == r){
        st[id].cnt += val;
        return;
    }

    int mid = l + ((r-l)>>1);

    if(pos <= mid){
        if(!st[id].l) st[id].l = ++nNode;
        update(st[id].l,l,mid,pos,val);    
    }
    else{
        if(!st[id].r) st[id].r = ++nNode;
        update(st[id].r, mid + 1, r, pos, val);
    }

    st[id].cnt = st[st[id].l].cnt + st[st[id].r].cnt;
}

int query(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id].cnt;

    int mid = l + ((r-l)>>1);

    int ans = 0;
    if(st[id].l) ans += query(st[id].l,l,mid,u,v);
    if(st[id].r) ans += query(st[id].r,mid+1,r,u,v);

    return ans;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        update(1,1,1e9,a[i],1);
    }

    while(q--){
        char type;
        cin >> type;
        if(type == '!'){
            int pos,val;
            cin >> pos >> val;
            update(1,1,1e9,a[pos],-1);
            update(1,1,1e9,val,1);
            a[pos] = val;
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << query(1,1,1e9,l,r) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}