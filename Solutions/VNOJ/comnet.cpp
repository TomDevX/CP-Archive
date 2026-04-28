/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-28 08:08:39
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
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
#include <string>
#include <utility>
#include <numeric>
#include <cstring>

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
    if(!fopen("comnet.INP", "r")) return;
    freopen("comnet.INP", "r", stdin);
    freopen("comnet.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2, M = 1e6+2;
int par[N], sz[N];
bool changed[M];

pii Es[M];
vpii E,E2;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n, int m){
    iota(par + 1, par + n + 1, 1);
    memset(sz, 0, sizeof(int)*(n+1));
    E.clear();
    memset(Es,0,sizeof(E[0])*m);
}   

void rest(int n, int m){
    memset(changed,0, sizeof(changed[0])*m);
    iota(par + 1, par + n + 1, 1);
    memset(sz, 0, sizeof(sz[0])*(n+1));
    E2.clear();
}

bool cmp(const pii& a, const pii& b){
    return a.se < b.se;
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

bool union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a,b);
    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;

    return true;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    E.reserve(M);
    E2.reserve(101);

    while(tc--){
        int n,m,q;
        cin >> n >> m >> q;

        init(n,m);

        for(int i = 1; i <= m; i++){
            int u,v,w;
            cin >> u >> v >> w;
            Es[i] = make_pair(u,v);
            E.eb(i,w);
        }   

        sort(all(E,0), cmp);

        while(q--){
            int k,s;
            cin >> k >> s;
            for(int i = 1; i <= s; i++){
                int id, w;
                cin >> id >> w;
                E2.eb(id,w);
                changed[id] = true;
            }

            sort(all(E2,0),cmp);

            int l1 = 0, l2 = 0;
            bool checked = false;
            while(l1 < sz(E) || l2 < sz(E2)){
                pii cur;
                if(l2 == sz(E2) || (l1 < sz(E) && E[l1].se < E2[l2].se)){
                    if(changed[E[l1].fi]) continue;
                    cur = E[l1];
                    l1++;
                }
                else{
                    cur = E2[l2];
                    l2++;
                }

                if(cur.se > E)
            }

            cout << (checked ? "YES" : "NO") << '\n';
            rest(n,m);
        }
    }
    
    return NAH_I_WOULD_WIN;
}