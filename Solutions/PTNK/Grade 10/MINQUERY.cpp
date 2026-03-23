/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-20 13:38:42
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cmath>
#include <algorithm>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;

void setup(){
    if(!fopen("MINQUERY.INP", "r")) return;
    freopen("MINQUERY.INP", "r", stdin);
    freopen("MINQUERY.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int pos, int val){
    if(l == r){
        st[id] = val;
        return;
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    if(pos <= mid) update(left,l,mid,pos,val);
    else update(left|1,mid+1,r,pos,val);
    st[id] = min(st[left],st[left|1]);
}

int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 2e9;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    return min(get(left,l,mid,u,v),get(left|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,q;
    cin >> n >> q;
    for(int i = 1; i <= 4*n; i++){
        st[i] = 2e9;
    }

    char type;
    int l,r;
    while(q--){
        cin >> type >> l >> r;
        if(type == 'S'){
            update(1,1,n,l,r);
        }
        else{
            cout << get(1,1,n,l,r) << '\n';
        }
    }
}