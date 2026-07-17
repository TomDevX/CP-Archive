/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-13 15:11:36
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
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
using vll = vector<long long>;

void setup(){
    if(!fopen("QUERY.INP", "r")) return;
    freopen("QUERY.INP", "r", stdin);
    freopen("QUERY.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+1;
int n,tc;
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

    st[id] = max(st[left],st[left|1]);
}

int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r<= v) return st[id];

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    return max(get(left,l,mid,u,v),get(left|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> tc;

    char type;
    int l,r;
    while(tc--){
        cin >> type >> l >> r;
        if(type == 'S'){
            update(1,1,n,l,r);
        }
        else cout << get(1,1,n,l,r) << '\n';
    }
}