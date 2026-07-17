/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-09 14:26:08
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Olympic 30 tháng 4 năm 2026 - Khối 10 - Bài 1
 *    source: https://sqrtoj.edu.vn/problem/edu017a
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
    if(!fopen("edu017a.INP", "r")) return;
    freopen("edu017a.INP", "r", stdin);
    freopen("edu017a.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

struct node{
    int maxn,minn;
};
node st[4*N];
int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id].minn = st[id].maxn = a[l];
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id].minn = min(st[lc].minn,st[lc|1].minn);
    st[id].maxn = max(st[lc].maxn,st[lc|1].maxn);
}

int get_min(int id, int l, int r){
    if(l == r) return l;
    if(st[id].minn == -1) return -1;
    int mid = l + ((r-l)>>1);
    if(st[id].minn == st[id<<1].minn){
        return get_min(id<<1,l,mid);
    }
    return get_min(id<<1|1,mid+1,r);
}

int get_max(int id, int l, int r){
    if(l == r) return l;
    if(st[id].maxn == -1) return -1;
    int mid = l + ((r-l)>>1);
    if(st[id].maxn == st[id<<1].maxn){
        return get_max(id<<1,l,mid);
    }
    return get_max(id<<1|1,mid+1,r);
}

void update(int id, int l, int r, int u, int v){
    if(l > v || r < u){
        return;
    }
    if(l >= u && r <= v){
        st[id].minn = st[id].maxn = -1;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    update(lc,l,mid,u,v);
    update(lc|1,mid+1,r,u,v);

    if(st[id<<1].minn == -1 && st[id<<1|1].minn == -1){
        st[id].minn = st[id].maxn = -1;
    }
    else if(st[id<<1].minn == -1){
        st[id] = st[id<<1|1];
    }
    else if(st[id<<1|1].minn == -1){
        st[id] = st[id<<1];
    }
    else{
        st[id].minn = min(st[id<<1].minn,st[id<<1|1].minn);
        st[id].maxn = max(st[id<<1].maxn,st[id<<1|1].maxn);
    }
}   
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    build(1,1,n);

    int ans = 0;
    while(true){
        int x = get_min(1,1,n), y = get_max(1,1,n);
        if(x == -1) break;
        if(x > y) swap(x,y);
        update(1,1,n,x,y);   
        
        ans++;
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}