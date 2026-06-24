/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-24 08:38:45
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: GOM XU VÀNG 
 *    source: DuTuyen_20260624.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("GCOINS.INP", "r")) return;
    freopen("GCOINS.INP", "r", stdin);
    freopen("GCOINS.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 13, M = 18, LOG = 32;

vi adj[N];
vpii Edges = {{0,0}};
int W[M], cnt_max[M], deg_in[N];
ll val[M][LOG];
bitset<N> visv;
bitset<M> need, vise, can_traverse, necess;

ll ans = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void format_input(){
    int w;
    for(int i = 1; i <= 5; i++){
        if(i&1){
            for(int j = 1; j <= 3; j++){
                cin >> w;

                int row = (i+1)/2;
                int u = 4*(row-1) + j, v = u + 1;
                adj[u].eb(v);
                adj[v].eb(u);
                

                W[sz(Edges)] = w;
                Edges.eb(u,v);
            }
        }
        else{
            int row = i>>1;
            for(int j = 1; j <= 4; j++){
                cin >> w;
                
                int u = 4*(row-1) + j, v = u + 4;
                adj[u].eb(v);
                adj[v].eb(u);
                
                W[sz(Edges)] = w;
                Edges.eb(u,v);
            }
        }
    }
}

void pre_process(){
    for(int i = 1; i <= 17; i++){
        int x = W[i];
        for(int k = 1; k < LOG; k++){
            if(x <= 0){
                cnt_max[i] = k-1;
                break;
            }

            val[i][k] = val[i][k-1] + ((x + 1)>>1);
            x >>= 1;
        }
    }
}

bool check(){
    for(int e = 1; e <= 17; e++){
        if(need[e] && !vise[e]){
            return false;
        }
    }

    int cnt_odd = 0;
    for(int u = 1; u <= 12; u++){
        if(visv[u] && deg_in[u]&1) cnt_odd++;
        if(cnt_odd > 2){
            return false;
        }
    }

    return true;
}

void dfs(int u){
    visv[u] = 1;
    for(int v : adj[u]){
        for(int e = 1; e <= 17; e++){
            if(((Edges[e].fi == u && Edges[e].se == v) || (Edges[e].fi == v && Edges[e].se == u)) && need[e]){
                if(!vise[e]){
                    vise[e] = true;
                    if(!visv[v]) dfs(v);
                }
                break;
            }
        }
    }
}

void reset(){
    visv.reset();
    vise.reset();
    need.reset();
    for(int i = 1; i <= 12; i++) deg_in[i] = 0;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    format_input();
    pre_process();

    for(int mask = 0; mask < (1 << 17); mask++){
        reset();
        bool ok = true;
        int st = -1;
    
        for(int e = 1; e <= 17; e++){
            int steps = cnt_max[e];
            if((mask >> (e-1)) & 1){
                int k = (steps % 2 != 0) ? steps : steps - 1;
                if(k <= 0){
                    ok = false;
                    break; 
                }
                
                need[e] = 1;
                deg_in[Edges[e].fi]++;
                deg_in[Edges[e].se]++;
                st = Edges[e].fi;
            } else {
                int k = (steps % 2 == 0) ? steps : steps - 1;
                if(k > 0) {
                    need[e] = 1;
                }
            }
        }
        
        if(!ok) continue;
    
        if(mask > 0){
            dfs(st);
        } 
        else if(mask == 0){
            for(int u = 1; u <= 12; u++){
                visv.reset(); vise.reset();
                dfs(u);
                ll sum = 0;
                for(int e = 1; e <= 17; e++){
                    if(vise[e]){
                        int k = (cnt_max[e] % 2 == 0) ? cnt_max[e] : cnt_max[e] - 1;
                        if(k > 0) sum += val[e][k];
                    }
                }
                ans = max(ans, sum);
            }
            continue;
        }
        
        if(check()){
            ll sum = 0;
            for(int e = 1; e <= 17; e++){
                int steps = cnt_max[e];
                if((mask >> (e-1)) & 1){
                    int k = (steps % 2 != 0) ? steps : steps - 1;
                    if(k > 0) sum += val[e][k];
                }
                else if(vise[e]){
                    int k = (steps % 2 == 0) ? steps : steps - 1;
                    if(k > 0) sum += val[e][k];
                }
            }
            ans = max(ans, sum);
        } 
    }

    cout << ans << '\n';    
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}