/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-01 08:32:09
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Các số “hơi nguyên tố”
 *    source: DT 01-06-2026.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Digit, Implementation
 *    complexity: O(n)
 *    note: All number with size < n can be all obtained with 1 -> x. So we just need to consider the case size of n
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>

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
    if(!fopen("likeprime.INP", "r")) return;
    freopen("likeprime.INP", "r", stdin);
    freopen("likeprime.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------

// ----------------------- [ FUNCTIONS ] -----------------------
bool is_kinda_snt(const string& s){
    int sum = 1;
    for(char ch : s){
        int c = ch - '0';
        sum *= c;
        if(sum > 7 || sum == 0) return false;
    }

    return sum == 2 || sum == 3 || sum == 5 || sum == 7;
}

ll solve(const string& s){
    int n = sz(s);
    ll res = 0;

    int diff = n;
    for(int i = 0; i < n; i++){
        if(s[i] != '1'){
            diff = i;
            break;
        }
    }

    for(int pos = 0; pos < n; pos++){
        for(int p : {2,3,5,7}){
            if(diff < pos){
                if(s[diff] > '1') res++;
            }
            else{
                if(p + '0' < s[pos]) res++;
                else if(p + '0' == s[pos]){
                    bool ok = true;
                    for(int i = pos+1; i < n; i++){
                        if(s[i] != '1'){
                            if(s[i] < '1') ok = false;
                            break;
                        }
                    }
                    res += ok;
                }
            }
        }
    }

    return res + 2LL*n*(n-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string l,r;
    cin >> l;
    cin >> r;
    cout << solve(r) - solve(l) + is_kinda_snt(l);
    
    return NAH_I_WOULD_WIN;
}