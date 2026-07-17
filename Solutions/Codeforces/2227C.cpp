/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-30 21:35:46
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Snowfall
 *    source: https://codeforces.com/contest/2227/problem/C
 *    submission: https://codeforces.com/contest/2227/submission/373104180
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n)
 *    note: For a number to be divisible by 6, it must has prime factor of 2 and 3. So that, the optimal way is that we keep the elements with factor 2 together and elements with factor 3 together far from each other as much as possibe, for the one that is already divisible by 6, we can't change anything, so just put it in the edge (for less effection), choose the side of factor that has less elements
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vi a(n+1);
        vi six,two,three,out;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] % 6 == 0) six.eb(a[i]);
            else if(a[i] % 2 == 0) two.eb(a[i]);
            else if(a[i] % 3 == 0) three.eb(a[i]);
            else out.eb(a[i]);
        }

        vi res(n+1);
        int idx = 1;
        if(sz(two) > sz(three)){
            for(int i : two) res[idx++] = i;
            for(int i : out) res[idx++] = i;
            for(int i : three) res[idx++] = i;
            for(int i : six) res[idx++] = i;
        }
        else{
            for(int i : six) res[idx++] = i;
            for(int i : two) res[idx++] = i;
            for(int i : out) res[idx++] = i;
            for(int i : three) res[idx++] = i;
        }

        for(int i = 1; i <= n; i++) cout << res[i] << ' ';
        cout << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}