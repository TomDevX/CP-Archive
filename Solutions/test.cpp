/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-24 12:22:20
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("test.INP", "r")) return;
    freopen("test.INP", "r", stdin);
    freopen("test.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2005, K = 15;

int a[N][N], cnt[N];
int X[3] = {1,-1,0};
int Y[3] = {0,0,1};
int n,m,k;
bitset<K> connected[K];
int tot = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void make_matrix(){
    int h1 = 1, h2 = n, c1 = 1, c2 = m;
    int cur = 0;
    int left = cnt[cur];
    while(h1 <= h2 && c1 <= c2){
        for(int i = c1; i <= c2; i++){
            if(left == 0){
                cur++;
                left = cnt[cur];
            }
            a[h1][i] = cur;
            left--;
        }
        h1++;
        if(h1 > h2) break;
        
        for(int i = h1; i <= h2; i++){
            if(left == 0){
                cur++;
                left = cnt[cur];
            }
            a[i][c2] = cur;
            left--;
        }
        c2--;
        if(c1 > c2) break;
        
        for(int i = c2; i >= c1; i--){
            if(left == 0){
                cur++;
                left = cnt[cur];
            }
            a[h2][i] = cur;
            left--;
        }
        h2--;
        if(h1 > h2) break;
        
        for(int i = h2; i >= h1; i--){
            if(left == 0){
                cur++;
                left = cnt[cur];
            }
            a[i][c1] = cur;
            left--;
        }
        c1++;
        if(c1 > c2) break;
    }
}

bool check(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> m >> k;
    for(int i = 0; i < k; i++) cin >> cnt[i];

    make_matrix();

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int t = 0; t < 3; t++){
                int x = i + X[t];
                int y = j + Y[t];
                if(check(x,y) && a[x][y] != a[i][j]){
                    if(!connected[a[x][y]][a[i][j]]){
                        connected[a[x][y]][a[i][j]] = connected[a[i][j]][a[x][y]] = 1;
                        tot++;
                    }
                }
            }
        }
    }

    if(tot == (k*(k-1))>>1){
        cout << "YES\n";
        for(int i = 1; i <= n ;i++){
            for(int j = 1; j <= m; j++){
                cout << a[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    else cout << "NO\n";
    
    // for(int i = 1; i <= n ;i++){
    //     for(int j = 1; j <= m; j++) cerr << a[i][j] << " \n"[j == m];
    // }
    return NAH_I_WOULD_WIN;
}