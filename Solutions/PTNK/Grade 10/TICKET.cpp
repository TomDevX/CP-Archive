/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-13 14:03:58
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
    if(!fopen("TICKET.INP", "r")) return;
    freopen("TICKET.INP", "r", stdin);
    freopen("TICKET.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+1;
int st[4*N], t[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void down(int id){
    int f = t[id];
    t[id] = 0;

    int left = id<<1;

    st[left] += f;
    t[left] += f;
    st[left|1] += f;
    t[left|1] += f;
}

void update(int id, int l, int r, int u, int v){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        st[id]++;
        t[id]++;
        return;
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    down(id);
    update(left,l,mid,u,v);
    update(left|1,mid+1,r,u,v);
    st[id] = max(st[left], st[left|1]);
}

int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    down(id);
    int mid = l + ((r-l)>>1);
    int left = id<<1;

    return max(get(left,l,mid,u,v), get(left|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,k,tc;
    cin >> n >> k >> tc;

    int l,r;
    while(tc--){
        cin >> l >> r;
        l++; r++;
        if(get(1,1,n,l,r-1) < k){
            update(1,1,n,l,r-1);
            cout << 1 << '\n';
        }
        else cout << 0 << '\n';
    }
}