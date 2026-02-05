/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-05 22:12:35
 *    country: Vietnam - VNM
 *    title: 
 *    source: 
 *    submission: 
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>
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
int n,q;
string s;
int l,r;

// ----------------------- [ FUNCTIONS ] -----------------------
namespace sub1{
    int ans = 1e9;

    bool check(){
        return max(n,q) <= 10;
    }

    bool ispalin(){
        // odd
        for(int i = l+1; i < r; i++){
            if(s[i-1] == s[i+1]) return true;
        }

        // even
        for(int i = l; i < r; i++){
            if(s[i] == s[i+1]) return true;
        }

        return false;
    }

    void backtrack(int idx, int cnt){
        if(idx > r){
            if(ans > cnt && !ispalin()){
                // dbg(s,ans);
                ans = cnt;
            }
            return;
        }

        backtrack(idx+1,cnt);
        char ori = s[idx];
        for(int i = 0; i < 3; i++){
            if(i + 'a' != ori){
                s[idx] = i + 'a';
                backtrack(idx+1,cnt+1);
            }
        }
        s[idx] = ori;
    }

    void solve(){
        while(q--){
            cin >> l >> r;
            backtrack(l,0);
            cout << ans << '\n';
            ans = 1e9;
        }
    }
}

namespace sub2{
    bool check(){
        for(int i = 1; i < n; i++) if(s[i] != s[i+1]) return false;
        return true;
    }

    void solve(){
        while(q--){
            cin >> l >> r;
            cout << (r-l+1) - ceil((r-l+1)/3) << '\n';
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> q;
    cin >> s;
    s = '#' + s;

    if(sub1::check()) return sub1::solve(),0;
    if(sub2::check()) return sub2::solve(),0;
    // if(sub3::check()) return sub3::solve(),0;
}