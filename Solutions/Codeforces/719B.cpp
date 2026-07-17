/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-26 01:44:06
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Anatoly and Cockroaches
 *    source: https://codeforces.com/contest/719/problem/B
 *    submission: https://codeforces.com/contest/719/submission/380154576
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy
 *    complexity: O(n)
 *    metacognition: Just finding the case when to swap and when to switch? >< No case like that -> How about dp[i][2] as 0 for black and 1 for red? >< can swap and change color and position -> Read editorial -> There are only 2 cases are rbrbrbrbrbrb... and brbrbrbr... => can get our min move through counting current wrong positions in those 2 cases, and then swap the min wrong pos of red and black, and the rest needs repainting
 *    note: Greedy | There are only 2 cases are brbrbrbr... and rbrbrbrb..., so we consider each case (each case process the same), count the current wrong positions, and then let the min wrong pos of red and black swap together (cost min(wrong red, wrong black)) and the leftovers we need to repaint (max(wrong red, wrong black) - min(wrong red, wrong black))
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("719B.INP", "r")) return;
    freopen("719B.INP", "r", stdin);
    freopen("719B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

char cases[N][2];
int n;
string s;

// ----------------------- [ FUNCTIONS ] -----------------------
void preprocess(){
    for(int i = 0; i < N; i++){
        cases[i][0] = (i&1 ? 'r' : 'b');
        cases[i][1] = (i&1 ? 'b' : 'r');
    }
}

int check_case(int id){
    int r = 0, b = 0;

    for(int i = 0; i < n; i++){
        if(s[i] != cases[i][id]){
            if(s[i] == 'r') r++;
            else b++;
        }
    }

    return max(r,b) - min(r,b) + min(r,b);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n;
    cin >> s;

    int ans = check_case(0);
    ans = min(ans, check_case(1));

    cout << ans;
}

int main(){
    fastio;
    setup();
    preprocess();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}