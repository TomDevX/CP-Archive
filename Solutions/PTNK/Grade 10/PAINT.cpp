/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-02 15:14:23
 *    done in: <none>
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

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("PAINT.INP", "r", stdin);
    freopen("PAINT.OUT", "w", stdout);
}

long long findh(long long n){
    long long l = 0, r = 54;
    while(l < r){
        long long k = l + ((r-l+1)>>1);
        if(n >= (1LL << (k)) - 2 + 1) l = k;
        else r = k-1;
    }
    return l;
}

int main(){
    fast();
    setup();
    
    long long n;
    cin >> n;
    if(n == 0){ }

    long long k = findh(n);

    // tim cha
    long long start_h_cur = (1LL << (k)) - 2 + 1;
    long long start_h_cha = (1LL << (k-1)) - 2 + 1;
    long long pos_cur = ((n-start_h_cur)%(1LL << (k-1)))*2 + (n >= start_h_cur + (1LL << (k-1)));
    // dbg(pos_cur,1);
    long long pos_cha = (n - start_h_cur)%(1LL << (k-1));
    long long cha = (pos_cha&1 ? start_h_cha + (1LL << (k-2)) + (pos_cha)/2 : start_h_cha + pos_cha/2);

    cout << cha << '\n';

    // tim con
    long long con1 = (1LL << (k+1)) - 2 + 1 + pos_cur;
    long long con2 = con1 + (1LL << (k));
    cout << con1 << ' ' << con2;
}