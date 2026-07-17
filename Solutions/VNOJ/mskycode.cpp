/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-11 21:12:25
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Sky Code
 *    source: https://oj.vnoi.info/problem/mskycode
 *    submission: https://oj.vnoi.info/submission/12702560
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Inclusion-Exclusion
 *    complexity: O(n* \sqrt{n} + n \log n)
 *    metacognition: We can count the divisors of each elements by iterating through their divisor and +1 to the counter. In each divisor d, we need to know how many four elements combo has the gcd of it = d. So only count the counter of d is not enough because maybe it's just a normal divisor instead of gcd. So we need to subtract out the counter of it with its multiple's calculated answers (iterate d decreasingly). To know how many combos available in the current counter, we use Combinatorics ((counter)C(4))
 *    note: Count the divisor appear in each elements, and count how many four elements combo are in it using nCk. Though we need to exclusion out the divisor's multiples's answer because they are already counted as gcd of those combos.
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
    if(!fopen("mskycode.INP", "r")) return;
    freopen("mskycode.INP", "r", stdin);
    freopen("mskycode.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e4+2;

int n;
int a[N];
ll cnt[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void rest(){
    memset(cnt,0,sizeof(cnt));
}

ll nck(ll x){
    if(x < 4) return 0;
    return x*(x-1)*(x-2)*(x-3)/24;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        for(int d = 1; d * d <= a[i]; d++){
            if(a[i] % d == 0){
                cnt[d]++;
                if(a[i]/d != d){
                    cnt[a[i]/d]++;
                }
            }
        }
    }

    for(int d = 1; d <= N-2; d++){
        cnt[d] = nck(cnt[d]);
    }

    for(int d = N-2; d >= 1; d--){
        for(int j = d*2; j <= N-2; j += d) cnt[d] -= cnt[j];
    }

    cout << cnt[1] << '\n';
    
    rest();
}

int main(){
    fastio;
    setup();

    while(cin >> n){
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}