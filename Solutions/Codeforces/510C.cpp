/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-30 14:41:38
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Fox And Names
 *    source: https://codeforces.com/problemset/problem/510/C
 *    submission: https://codeforces.com/problemset/submission/510/376594618
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Topo Sort
 *    complexity: O(n^3)
 *    note: Topo the alphabet
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <queue>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("510C.INP", "r")) return;
    freopen("510C.INP", "r", stdin);
    freopen("510C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 30;

vi adj[N];
int deg_in[N];
bool vis[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    vs a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    for(int i = 1; i < n; i++){
        for(int j = i + 1; j <= n; j++){
            bool diff = false;
            for(int k = 0; k < min(sz(a[i]), sz(a[j])); k++){
                if(a[i][k] != a[j][k]){
                    diff = true;
                    adj[a[i][k] - 'a'].eb(a[j][k] - 'a');
                    deg_in[a[j][k] - 'a']++;
                    break;
                }
            }
            if(!diff && sz(a[i]) >= sz(a[j])){
                cout << "Impossible";
                return 0;
            }
        }
    }

    string trace;
    queue<int> qu;
    for(int i = 0; i < 26; i++){
        if(deg_in[i] == 0){
            qu.push(i);
        }
    }

    int cnt = 0;

    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        trace += (u + 'a');
        cnt++;

        for(int v : adj[u]){
            deg_in[v]--;
            if(deg_in[v] == 0){
                qu.push(v);
            }
        }
    }

    if(cnt != 26){
        cout << "Impossible";
        return 0;
    }

    for(char c : trace) cout << c;
    
    return NAH_I_WOULD_WIN;
}