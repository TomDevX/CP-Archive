/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-19 17:09:30
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: sqrt(n²+n+X)
 *    source: https://atcoder.jp/contests/abc420/tasks/abc420_g
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <stdio.h>

#define ll long long
#define N 20000005

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
ll ans[N];
ll c;

// ----------------------- [ FUNCTIONS ] -----------------------
void add(ll d){
    ll n = (c/d + d - 2)/4;
    ans.eb(n);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    ll x;
    cin >> x;

    c = 1 - 4*x;

    ll V = abs(c);

    for(ll d = 1; d * d <= V; d++){
        if(V%d != 0) continue;

        add(d);
        add(-d);
        add(-c/d);
        add(c/d);
    }

    sort(all(ans,0));
    filter(ans,0);

    cout << sz(ans) << '\n';
    for(ll i : ans) cout << i << ' ';
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