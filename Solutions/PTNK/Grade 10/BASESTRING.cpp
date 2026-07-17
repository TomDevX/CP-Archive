/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-06 04:02:43
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Xâu cơ sở
 *    source: BT_20260406.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: String
 *    complexity: O(1)
 *    note: If string a and b has the same base, so a + b = b + a, if this condition doesn't meet, answer = NO. Since they have the same base, our answer is the string with gcd(|a|,|b|) size
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
    if(!fopen("BASESTRING.INP", "r")) return;
    freopen("BASESTRING.INP", "r", stdin);
    freopen("BASESTRING.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
int gcd(int a, int b){
    while(b != 0){
        int tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string a,b;
    cin >> a >> b;

    if(a + b != b + a){
        cout << "NO";
        return 0;
    }
    
    int n = sz(a), m = sz(b);

    cout << a.substr(0,gcd(n,m));
    
    return NAH_I_WOULD_WIN;
}