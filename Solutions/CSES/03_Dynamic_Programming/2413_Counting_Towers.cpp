/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-04 14:51:29
 *    country: Vietnam - VNM
 *    title:
 *    source: 
 *    submission: https://cses.fi/paste/67df7ff1543072a9f68403/
 * ----------------------------------------------------------
 *    algorithm: Dynamic Programming, AdHoc
 *    complexity: O(n)
 *    note: We can divide each floor into these 6 types (check below), each type can go with other different types so we have to handle those cases
 **/
 
#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;
 
void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}
 
// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7;
const int N = 1e6;
ll dp[N][7];
 
// ----------------------- [ FUNCTIONS ] -----------------------
ll add(ll a, ll b){
    return (a+b)%MOD;
}

//                                  
// │                    │     #    │            │          │         
// │                    │     #    │            │          │         
// │     Type 1         │     #    │   Type 2   │          │         
// │                    │     #    │            │          │         
// │                    │     #    │            │          │         
// │                    │     #    │            │          │         
// └────────────────────┘     #    └────────────┴──────────┴         
//                            #                                      
// ##################################################################   
//                            #                                      
//                            #                                      
// │                    │     #    │            │          │         
// │                    │     #    │            │          │         
// │      Type 3        │     #    │            │          │         
// │                    │     #    │    Type 4  │          │         
// │                    │     #    │            │          │         
// │                    │     #    │            │          │         
// │                    │     #    │            │          │         
// │                    │     #    │            │          │         
//                            #                                      
// ######################################################################
//                            #                                      
//                            #                                      
// │           │        │     #    │            │          │         
// │           │        │     #    │            │          │         
// │           │        │     #    │            │          │         
// │ Type 5    │        │     #    │   Type 6   │          │         
// │           │        │     #    │            │          │         
// │           │        │     #    │            │          │         
// │           │        │     #    │            │          │         
// └───────────┘        │     #    │            └──────────┴         
//                            #                                      
//                            #                                      
//                            #                                      
void init(){
    dp[1][1] = dp[1][2] = 1;
    for(int i = 2; i <= N; i++){
        ll *prev = dp[i-1];
        dp[i][1] = add(add(add(add(add(prev[1],prev[2]),prev[3]),prev[4]),prev[5]),prev[6]);
        dp[i][2] = add(add(add(add(add(prev[1],prev[2]),prev[3]),prev[4]),prev[5]),prev[6]);
        dp[i][3] = add(prev[1],prev[3]);
        dp[i][4] = add(prev[2], add(prev[4],add(prev[5],prev[6])));
        dp[i][5] = add(prev[2], add(prev[4],add(prev[5],prev[6])));
        dp[i][6] = add(prev[2], add(prev[4],add(prev[5],prev[6])));
    }
}
 
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
 
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
 
        ll sum = 0;
        for(int i = 1; i <= 6; i++){
            sum = (sum + dp[n][i])%MOD;
        }
 
        cout << sum << '\n';
    }
}