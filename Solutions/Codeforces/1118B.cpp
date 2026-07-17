/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-30 02:02:33
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tanya and Candies
 *    source: https://codeforces.com/contest/1118/problem/B
 *    submission: https://codeforces.com/contest/1118/submission/380633450
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n)
 *    metacognition: Oh just count if sum_odd - i == sum_even or sum_even - i == sum_odd based on the parity of the position >< read wrong statement, the parity will change on removing element -> Now need to count separate suffix sum array to count odd, even from right to left then iterate from left to right and consider the cases
 *    note: Make a suffix sum for sum of odd/even elements from right to left. Iterate from left to right to count for the answer, consider the cases to get the parity of the suffix for each i, also save the prefix odd/even sum.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x)
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
    if(!fopen("1118B.INP", "r")) return;
    freopen("1118B.INP", "r", stdin);
    freopen("1118B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

bitset<N> stat;
int sum1[N], sum2[N], a[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    
    for(int i = n; i >= 1; i--){
        stat[i] = !stat[i+1];
        
        if(stat[i]) sum1[i] += a[i];
        else sum2[i] += a[i];
        
        sum1[i] += sum1[i+1];
        sum2[i] += sum2[i+1];
    }
    
    int ans = 0;
    int sum_odd = 0, sum_even = 0;
    for(int i = 1; i <= n; i++){
        if(i&1){
            if(stat[i+1]){
                ans += (sum_odd + sum1[i+1] == sum_even + sum2[i+1]);
            }
            else ans += (sum_odd + sum2[i+1] == sum_even + sum1[i+1]);
            sum_odd += a[i];
        }
        else{
            if(stat[i+1]){
                ans += (sum_odd + sum2[i+1] == sum_even + sum1[i+1]);
            }
            else ans += (sum_odd + sum1[i+1] == sum_even + sum2[i+1]);
            sum_even += a[i];
        }
    }

    cout << ans;
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