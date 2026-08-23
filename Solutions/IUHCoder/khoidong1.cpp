/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-08-16 09:04:00
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Bầy mèo nổi loạn
 *    source: https://oj.iuhcoder.com/problem/khoidong1
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
    if(!fopen("khoidong1.INP", "r")) return;
    freopen("khoidong1.INP", "r", stdin);
    freopen("khoidong1.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int a[7];

// ----------------------- [ FUNCTIONS ] -----------------------
ll binh(int x){
    return 1LL*x*x;
}

bool check(){
    return binh(a[1] + a[2]) + binh(a[3] + a[4]) == binh(a[5] + a[6]);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n = 6;
    for(int i = 1; i <= n; i++) cin >> a[i];

    sort(all(a,1));

    do{
        if(check()){
            cout << "YES\n";
            return;
        }
    }while(next_permutation(all(a,1)));
    cout << "NO\n";
}

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;  
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}