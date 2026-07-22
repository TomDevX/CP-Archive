/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-21 21:07:18
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: 
 *    source: 
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
#include <cmath>
#include <utility>

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
    if(!fopen("test2.INP", "r")) return;
    freopen("test2.INP", "r", stdin);
    freopen("test2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;

int pref[N], suff[N];
int prefD[N];
int n;
string s;

pii stL[4*N], stR[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void precalc(){
    for(int i = 1; i <= n; i++){
        pref[i] = pref[i-1] + (s[i] == 'D' ? -1 : 1);    
        prefD[i] = prefD[i-1] + (s[i] == 'D');
        // cerr << pref[i] << ' ';
    } 
    for(int i = n; i >= 1; i--){
        suff[i] = suff[i+1] + (s[i] == 'D' ? -1 : 1);
    }
    // cerr << '\n';
}

void buildL(int id, int l, int r){
    if(l == r){
        stL[id] = {pref[l], l};
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    buildL(lc, l, mid);
    buildL(lc|1, mid+1, r);

    if(stL[lc|1].fi <= stL[lc].fi){
        stL[id] = stL[lc|1];
    }
    else stL[id] = stL[lc];
}

void buildR(int id, int l, int r){
    if(l == r){
        stR[id] = {suff[l], l};
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    buildR(lc, l, mid);
    buildR(lc|1, mid+1, r);

    if(stR[lc].fi <= stR[lc|1].fi){
        stR[id] = stR[lc];
    }
    else stR[id] = stR[lc|1];
}

pii queryL(int id, int l, int r, int u, int v){
    if(l > v || r < u){
        return {1e9, -1};
    }
    if(l >= u && r <= v){
        return stL[id];
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    pii L = queryL(lc,l,mid,u,v);
    pii R = queryL(lc|1,mid+1,r,u,v);

    if(R.fi <= L.fi) return R;
    return L;
}

pii queryR(int id, int l, int r, int u, int v){
    if(l > v || r < u){
        return {1e9, -1};
    }
    if(l >= u && r <= v){
        return stR[id];
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    pii L = queryR(lc,l,mid,u,v);
    pii R = queryR(lc|1,mid+1,r,u,v);

    if(L.fi <= R.fi) return L; 
    return R;
}

int solve(int l, int r){
    pii L_idx = queryL(1,1,n,l,r);  
    int ans_L = min(0,pref[L_idx.se] - pref[l-1]);
    
    pii R_idx = queryR(1,1,n,l,r);
    int ans_R = min(0,suff[R_idx.se] - suff[r+1]);

    int ans = max(0, pref[l-1] - pref[r]);
    // dbg(make_pair(L_idx,R_idx),1);

    return max({abs(ans_L), abs(ans_R), ans});
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n;
    cin >> s;
    s = "#" + s;

    precalc();
    buildL(1,1,n);
    buildR(1,1,n);

    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << solve(l,r) << '\n';
    }
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