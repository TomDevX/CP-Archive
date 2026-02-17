/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-17 12:30:46
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: You Soared Afar With Grace
 *    source: https://codeforces.com/problemset/problem/2084/C
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vi a(n+1), b(n+1), pos(n+1);

        for(int i = 1; i <= n; i++){
            cin >> a[i];
            pos[a[i]] = i;
        }
        for(int i = 1; i <= n; i++) cin >> b[i];

        int cnt = 0;
        bool check = true;
        for(int i = 1; i <= n; i++){
            if(a[i] == b[i]){
                cnt++;
                if(cnt > 1){
                    check = false;
                    break;
                }
            }
        }

        if(!check){
            cout << -1 << '\n';
            continue;
        }

        for(int i = 1; i <= n; i++){
            b[i] = pos[b[i]];
        }
        for(int i = 1; i <= n; i++){
            pos[b[i]] = i;
        }

        vector<pii> poss;
        for(int i = 1; i <= n; i++){
            if(b[i] != a[i]){
                poss.eb(pos[b[i]],pos[a[i]]);
                swap(b[pos[b[i]]], b[pos[a[i]]]);
                swap(pos[b[i]], pos[a[i]]);
            }
        }

        cout << sz(poss) << '\n';
        for(int i = 0; i < sz(poss); i++){
            cout << poss[i].fi << ' ' << poss[i].se << '\n';
        }
    }
}