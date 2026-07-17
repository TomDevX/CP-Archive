/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-06 17:06:25
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: LÊN MÁY BAY
 *    source: DT 06-07-2026.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
 *    note: 
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
    if(!fopen("plane.INP", "r")) return;
    freopen("plane.INP", "r", stdin);
    freopen("plane.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1002;

char a[N][7];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 6; j++) cin >> a[i][j];
    }

    int need = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 3; j++){
            if(a[i][j] != a[i][6-j+1]){
                need++;
                if(a[i][j] != 'X') a[i][j] = 'X';
                else a[i][6-j+1] = 'X';
            }
        }
    }

    if(m < need){
        cout << "Impossible";
        return;
    }
    
    m -= need;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 3; j++){
            if(m >= 2 && a[i][j] == a[i][6-j+1] && a[i][j] == '.'){
                m -= 2;
                a[i][j] = a[i][6-j+1] = 'X';
            }
        }
    }

    if(m){
        cout << "Impossible";
        return;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 6; j++) cout << a[i][j];
        cout << '\n';
    }
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