/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-29 20:47:56
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: LRC and VIP
 *    source: https://codeforces.com/contest/2107/problem/A
 *    submission: https://codeforces.com/contest/2107/submission/376538760
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy
 *    complexity: O(n)
 *    note: It's always a Yes unless all elements are the same, just take the max element (for not to be same with any gcd) as one group and the others as 1 group
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

        int maxn = 0;
        for(int i = 1; i <= n; i++) cin >> a[i], maxn = max(maxn, a[i]);

        bool all_same = true;
        for(int i = 2; i <= n; i++){
            if(a[i] != a[i-1]){
                all_same = false;
                break;
            }
        }

        if(all_same) cout << "No\n";
        else{
            cout << "Yes\n";
            for(int i = 1; i <= n; i++){
                if(a[i] == maxn) cout << 2 << ' ';
                else cout << 1 << ' ';
            }
            cout << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}