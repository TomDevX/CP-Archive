/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-13 13:20:07
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
    if(!fopen("SUM.INP", "r")) return;
    freopen("SUM.INP", "r", stdin);
    freopen("SUM.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
ll st[4*N];

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
    st[id] = st[left] + st[left|1];
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v){
        return st[id];
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;
    return get(left,l,mid,u,v) + get(left|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,tc;
    cin >> n >> tc;

    int l,r;
    char type;
    while(tc--){
        cin >> type >> l >> r;
        if(type == 'Q'){
            cout << get(1,1,n,l,r) << '\n';
        }
        else{
            update(1,1,n,l,r);
        }
    }
}