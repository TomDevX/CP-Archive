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
#include <math.h>
#include <stdlib.h>

#define ll long long
#define N 20000005

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
ll ans[N];
ll c;
int idx = -1;

// ----------------------- [ FUNCTIONS ] -----------------------
void add(ll d){
    ll n = (c/d + d - 2)/4;
    ans[++idx] = n;
}

int cmp(const void* x, const void *y){
    ll vx = *(ll*) x, vy = *(ll*) y;
    if(vx < vy) return -1;
    if(vx > vy) return 1;
    return 0;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    ll x;
    scanf("%lld", &x);

    c = 1 - 4*x;

    ll V = (c < 0 ? -c : c);

    for(ll d = 1; d * d <= V; d++){
        if(V%d != 0) continue;

        add(d);
        add(-d);
        add(-c/d);
        add(c/d);
    }

    qsort(ans,idx+1, sizeof(ll), cmp);
    
    int unique_idx = 0;
    for (int i = 0; i <= idx; i++) {
        if (ans[i] != ans[unique_idx]) {
            ans[++unique_idx] = ans[i];
        }
    }
    int sz = unique_idx + 1;

    printf("%d\n", sz);
    for(int i = 0; i < sz; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
}

int main(){

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return 0;
}