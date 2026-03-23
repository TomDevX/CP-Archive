/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-19 09:29:48
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
    if(!fopen("MODSEQ.INP", "r")) return;
    freopen("MODSEQ.INP", "r", stdin);
    freopen("MODSEQ.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m;
const int N = 1e5+2;
vi a(N);
int st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id] = a[l];
        return;
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;
    build(left,l,mid);
    build(left|1,mid+1,r);
    st[id] = min(st[left],st[left|1]);
}

int get(int id, int l, int r, int x){
    if(l == r){
        if(st[id] > x) return -1;
        return st[id];
    }
    
    int mid = l + ((r-l)>>1);
    int left = id<<1;
    if(st[left] <= x) return get(left,l,mid,x);
    return get(left|1,mid+1,r,x);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1,1,n);

    cin >> m;
    int x;
    for(int i = 1; i <= m; i++){
        cin >> x;
        int y = get(1,1,n,x);
        // dbg(y,x);
        while(y != -1){
            x %= y;
            y = get(1,1,n,x);
        }
        cout << x << ' ';
    }
}