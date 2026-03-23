/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-13 14:28:36
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
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
using vll = vector<long long>;

void setup(){
    if(!fopen("OS.INP", "r")) return;
    freopen("OS.INP", "r", stdin);
    freopen("OS.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct query{
    int l,r;
};

struct node{
    bool t,val;
};

const int N = 2e5+2;
vector<query> queries(N);
node st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void down(int id){
    if(st[id].t){
        int left = id<<1;

        st[left].val = st[left|1].val = st[left].t = st[left|1].t = 1;

        st[id].t = 0;
    }
}

void update(int id, int l, int r ,int u, int v){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        st[id].val = st[id].t = 1;
        return;
    }

    down(id);
    int mid = l + ((r-l)>>1);
    int left = id<<1;
    update(left,l,mid,u,v);
    update(left|1,mid+1,r,u,v);
    st[id].val = st[left].val | st[left|1].val;
}

int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v){
        return st[id].val;
    }

    down(id);
    int mid = l + ((r-l)>>1);
    int left = id<<1;
    return get(left,l,mid,u,v) | get(left|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,m;
    cin >> n >> m;

    vi cand = {0};
    cand.reserve(2*m+1);

    for(int i = 1; i <= m; i++){
        cin >> queries[i].l >> queries[i].r;
        cand.eb(queries[i].l);
        cand.eb(queries[i].r);
    }

    sort(all(cand,1));
    cand.erase(unique(all(cand,1)),cand.end());
    n = sz(cand);

    for(int i = 1; i <= m; i++){
        queries[i].l = lower_bound(all(cand,1),queries[i].l) - cand.begin();
        queries[i].r = lower_bound(all(cand,1),queries[i].r) - cand.begin();
    }

    int ans = 0;
    for(int i = m; i >= 1; i--){
        if(get(1,1,n,queries[i].l,queries[i].r) == 0){
            ans++;
        }
        update(1,1,n,queries[i].l,queries[i].r);
    }
    cout << ans;
}