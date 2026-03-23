/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-08 09:19:54
 *    done in: <none>
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

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("EQUALTRIPLE.INP", "r", stdin);
    freopen("EQUALTRIPLE.OUT", "w", stdout);
}

int main(){
    fast();
    setup();
    
    vector<long long> a(3);
    for(int i = 0; i < 3; i++){
        cin >> a[i];
    }
    sort(all(a,0));
    long long final = a[2] + (a[1] - a[0]);
    cout << final-a[0];
}