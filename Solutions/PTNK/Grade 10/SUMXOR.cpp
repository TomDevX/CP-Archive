/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-12 09:48:15
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
    if(!fopen("SUMXOR.INP", "r")) return;
    freopen("SUMXOR.INP", "r", stdin);
    freopen("SUMXOR.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;
ll suff[N][22];
int a[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void phantich(){
    for(int i = n; i > 1; i--){
        for(int j = 0; j <= 21; j++){
            suff[i][j] += (a[i] >> j)&1;
            suff[i][j] += suff[i+1][j];
        }
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

    phantich();

    ll ans = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= 21; j++){
            if((a[i] >> j) & 1){
                ans += (1LL << j)*(n - i - suff[i+1][j]);
            }
            else{
                ans += (1LL << j)*suff[i+1][j];
            }
        }
    }

    cout << ans;
}