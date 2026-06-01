/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-01 22:08:15
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Find the Zero
 *    source: https://codeforces.com/problemset/problem/2209/C
 *    submission: https://codeforces.com/problemset/submission/2209/376916461
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Interactive
 *    complexity: O(n)
 *    note: Best strategy is to ask [i,i+1] and i += 2 and continue. This checks that only at most one adjacent 0s sequence if all of those queries failed, after that we just list all first 4 number cases: 1020, 1002, 0120, 0102, 0012. To check, we query(1,3) and query(1,4) and remove them. At the first phase, we can leave the [1,2] query because we can alreasy solve it in phase 2
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
    if(!fopen("2182C.INP", "r")) return;
    freopen("2182C.INP", "r", stdin);
    freopen("2182C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
void ask(int a, int b){
    cout << "? " << a << ' ' << b << endl;
}

bool get(){
    bool ans;
    cin >> ans;
    return ans;
}

void answer(int x){
    cout << "! " << x << endl;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc = 1;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        n <<= 1;

        bool isgood = false;
        for(int i = 3; i+1 <= n; i+=2){
            ask(i,i+1);
            bool ans = get();
            if(ans){
                answer(i);
                isgood = true;
                break;
            }
        }

        if(!isgood){
            ask(1,3);
            bool ans = get();
            if(ans) answer(1);
            else{
                ask(1,4);
                ans = get();
                if(ans) answer(1);
                else answer(2);
            }
        }
    }
    
    return NAH_I_WOULD_WIN;
}