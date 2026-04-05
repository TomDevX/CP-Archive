/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-21 23:52:56
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: String occurences 2 - KMP Approach
 *    source: https://marisaoj.com/problem/165
 *    submission: https://marisaoj.com/submission/1132019
 *    status: AC
 * ----------------------------------------------------------
 *    tags: KMP
 *    complexity: O(n + m) 
 *    note: Typical KMP algo
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
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
    if(!fopen("165_KMP.INP", "r")) return;
    freopen("165_KMP.INP", "r", stdin);
    freopen("165_KMP.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
vi pf(string &s){
    int n = sz(s);
    vi pi(n);
    int j = 0;
    for(int i = 1; i < n; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string a,b;
    cin >> a >> b;
    int m = sz(b);

    string t = b+"#" +a;

    vi pi = pf(t);
    int ans = 0;
    for(int i = 2*m; i < sz(t); i++){
        if(pi[i] == m) ans++;
    }
    cout<< ans;
    
    return NAH_I_WOULD_WIN;
}