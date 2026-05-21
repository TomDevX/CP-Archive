/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-21 15:30:45
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: ANAGRAM
 *    source: https://oj.vnoi.info/problem/fc051_anagram
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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
    if(!fopen("fc051_anagram.INP", "r")) return;
    freopen("fc051_anagram.INP", "r", stdin);
    freopen("fc051_anagram.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 4005;

int pref[2][N][26];
int (&prefA)[N][26] = pref[0];
int (&prefB)[N][26] = pref[1];
int n,m;

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int len){
    for(int i = 1; i + len - 1 <= n; i++){
        int ir = i + len - 1;
        for(int j = 1; j + len - 1 <= m; j++){
            int jr = j + len - 1;
            bool good = true;

            for(int c = 0; c < 26; c++){
                if(prefA[ir][c] - prefA[i-1][c] != prefB[jr][c] - prefB[j-1][c]){
                    good = false;
                    break;
                }
            }

            if(good) return true;
        }
    }
    return false;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string a,b;
    cin >> a >> b;
    n = sz(a), m = sz(b);
    a = "#" + a;
    b = "#" + b;

    for(int i = 1; i <= n; i++){
        prefA[i][a[i] - 'a']++;
        for(int j = 0; j < 26; j++){
            prefA[i][j] += prefA[i-1][j];
        }
    }
    for(int i = 1; i <= m; i++){
        prefB[i][b[i] - 'a']++;
        for(int j = 0; j < 26; j++){
            prefB[i][j] += prefB[i-1][j];
        }
    }

    int l = 1, r = min(n,m), ans = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);

        if(check(mid)){
            ans = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}