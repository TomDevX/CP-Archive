/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-13 13:03:15
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
    if(!fopen("XORSUM.INP", "r")) return;
    freopen("XORSUM.INP", "r", stdin);
    freopen("XORSUM.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 1e5+2;
pii suff[N][22]; // đếm {tổng số 1; số lần xuất hiện chẵn}
int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void preprocess(){
    for(int i = n; i >= 1; i--){
        for(int j = )
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    preprocess();

    for(int i = n; i >= 1; i--){

    }
}