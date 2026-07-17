/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-13 12:43:24
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Prepend and Append 
 *    source: https://codeforces.com/contest/1791/problem/C
 *    submission: https://codeforces.com/contest/1791/submission/366453264
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n)
 *    note: Just iterate through all the borders to see if they are different
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("debuggingz.h")
#include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#ifdef LOCAL
    #include <iomanip>
    #include <ctime>
    #include <sys/resource.h>
    struct Statistic_Tracker {
        ~Statistic_Tracker() {
            struct rusage usage;
            getrusage(RUSAGE_SELF, &usage);
            double time = 1.0 * clock() / CLOCKS_PER_SEC;
            
            double mem = usage.ru_maxrss;
            #ifdef __APPLE__
                mem /= (1024.0 * 1024.0);
            #else
                mem /= 1024.0;
            #endif
    
            cerr << "\033[1;32m--------------------------------\033[0m\n";
            cerr << "\033[1;32mNAH I'D WIN!\033[0m | ";
            cerr << "\033[1;33mTime: " << fixed << setprecision(3) << time << "s\033[0m | ";
            cerr << "\033[1;36mMem: " << fixed << setprecision(2) << mem << "MB\033[0m\n";
        }
    } __tracker;
#endif

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
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
        string s;
        cin >> s;
        s = '#' + s;

        int cnt = 0;
        for(int i = 1; i <= n/2; i++){
            if((s[i] - '0')^(s[n-i+1] - '0')){
                cnt+=2;
            }
            else break;
        }
        cout << n-cnt << '\n';
    }
}   