/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-19 10:38:56
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
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
    if(!fopen("rem.INP", "r")) return;
    freopen("rem.INP", "r", stdin);
    freopen("rem.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e6+2;
int par[N];

// ----------------------- [ FUNCTIONS ] -----------------------
int find_set(int u){
    return (par[u] == u ? u : par[u] = find_set(par[u]));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    for(int i = 1; i <= 2e6; i++){
        par[i] = i;
    }

    par[a[1]] = a[1]+1;
    for(int i = 2; i <= n; i++){
        a[i] = find_set(a[i]);
        par[a[i]] = a[i]+1;
    }
    for(int i = 1; i <= n; i++) cout << a[i] << ' ';
}