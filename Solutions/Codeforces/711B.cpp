/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-28 22:14:02
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Chris and Magic Square
 *    source: https://codeforces.com/contest/711/problem/B
 *    submission: https://codeforces.com/contest/711/submission/380519565
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n^2)
 *    metacognition: Just check all the rows, cols, diagonal,... and check if any number can fit it 
 *    note: A number can fit and good in that position when their all other rows and cols and main,second diagonal has the same sum, and 0's row and 0's col has same sum - whose sum must be strictly lower than the other sums. Consider the cases if 0 in on both diagonal and row, col
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>

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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("711B.INP", "r")) return;
    freopen("711B.INP", "r", stdin);
    freopen("711B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 502;

int a[N][N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    pii target;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> a[i][j];
            if(a[i][j] == 0) target = {i,j};
        }
    }

    ll good = -1;

    // main diagonal
    ll sum = 0;
    for(int i = 1; i <= n; i++){
        int x = i, y = i;
        if(target.fi == x && target.se == y){
            sum = -1;
            break;
        }
        sum += a[x][y];
    }

    if(sum > -1) good = sum;
    sum = 0;

    // second diagonal
    for(int i = 1; i <= n; i++){
        int x = i, y = n-i+1;
        if(target.fi == x && target.se == y){
            sum = -1;
            break;
        }
        sum += a[x][y];
    }

    if(sum > -1){
        if(good == -1) good = sum;
        else if(good != sum){
            cout << -1;
            return;
        }
    }
    sum = 0;

    // rows
    for(int i = 1; i <= n; i++){
        ll sum = 0;
        for(int j = 1; j <= n; j++){
            if(i == target.fi && j == target.se){
                sum = -1;
                break;
            }
            sum += a[i][j];
        }
        if(sum > -1){
            if(good == -1) good = sum;
            else if(good != sum){
                cout << -1;
                return;
            }
        }
    }

    // cols
    for(int j = 1; j <= n; j++){
        ll sum = 0;
        for(int i = 1; i <= n; i++){
            if(i == target.fi && j == target.se){
                sum = -1;
                break;
            }
            sum += a[i][j];
        }
        if(sum > -1){
            if(good == -1) good = sum;
            else if(good != sum){
                cout << -1;
                return;
            }
        }
    
    }

    if(good == -1){
        cout << 67;
        return;
    }

    // target row and col
    ll sum_col = 0, sum_row = 0;
    for(int i = 1; i <= n; i++){
        sum_col += a[i][target.se]; 
    }
    for(int j = 1; j <= n; j++){
        sum_row += a[target.fi][j];
    }

    bool ok = (sum_col == sum_row && sum_col < good);

    if(!ok){
        cout << -1;
        return;
    }

    if(target.fi == target.se){
        ll sum_diag = 0;
        for(int i = 1; i <= n; i++){
            sum_diag += a[i][i];
        }
        ok &= (sum_diag == sum_col);
    }

    if(!ok){
        cout << -1;
        return;
    }

    if(target.se == n-target.fi+1){
        ll sum_diag = 0;
        for(int i = 1; i <= n; i++){
            sum_diag += a[i][n-i+1];
        }
        ok &= (sum_diag == sum_col);
    }

    if(!ok){
        cout << -1;
        return;
    }

    cout << good - sum_col;
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