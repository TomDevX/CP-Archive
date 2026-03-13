/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-13 22:38:27
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
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
#include "TomDev.h"
#define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5;
pii st[N+2][18];
int lg[N+2];

// ----------------------- [ FUNCTIONS ] -----------------------
pii get(int l, int r){
    if(l > r) return {0,0};
    int k = lg[r-l+1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++){
        cin >> st[i][0].fi;
        st[i][0].se = i;
        if(i > 1) lg[i] = lg[i>>1] + 1;
    }

    for(int k = 1; k <= 17; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st[i][k] = max(st[i][k-1], st[i + (1 << (k-1))][k-1]);
        }
    }

    while(q--){
        int l,r;
        cin >> l >> r;

        pii a = get(l,r);
        pii b = max(get(l,a.se-1), get(a.se+1,r));

        cout << a.fi + b.fi << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}