/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-25 10:06:09
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Jellyfish and Mex - Approach 3
 *    source: https://codeforces.com/contest/1875/problem/D
 *    submission: https://codeforces.com/contest/1875/submission/375996127
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming, Convex Hull Trick
 *    complexity: O(n)
 *    note: Like approach 2 but more optimized with upgraded convex hull trick
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <deque>

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
    if(!fopen("1875D.INP", "r")) return;
    freopen("1875D.INP", "r", stdin);
    freopen("1875D.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll INF = 2e18;
const int N = 5005;

struct Line{
    ll m, b;

    Line(ll _m = 0, ll _b = 0) : m(_m), b(_b) {};
};

deque<Line> dq;

vi buckets[N];

// ----------------------- [ FUNCTIONS ] -----------------------
ll f(Line L, ll x){
    return L.m*x + L.b;
}

bool isBad(Line& l1, Line& l2, Line& l3){
    return (l1.m - l2.m)*(l2.b - l3.b) >= (l2.m - l3.m)*(l1.b - l2.b);
}

ll query(ll x){
    while(sz(dq) >= 2 && f(dq[0],x) > f(dq[1],x)) dq.pop_front();
    return f(dq[0],x);
}

void add(ll m, ll b){
    Line cur = Line(m,b);
    while(sz(dq) >= 2 && isBad(dq[sz(dq) - 2], dq.back(), cur)) dq.pop_back();
    dq.push_back(cur);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        dq.clear();

        vi cnt(n+1);
        for(int i = 1; i <= n; i++){
            int x;
            cin >> x;
            if(x < n) cnt[x]++;

            buckets[i].clear();
        }

        int mex = 0;
        while(cnt[mex]){
            buckets[cnt[mex]].eb(mex);
            mex++;
        }

        vll dp(n+1,INF);
        dp[mex] = 0;

        int cur_mex = mex;

        for(int v = 1; v <= n; v++){
            for(int i : buckets[v]){
                while(cur_mex > i){
                    if(dp[cur_mex] != INF) add(cur_mex,dp[cur_mex]);
                    cur_mex--;

                    // skippable because if we have a middleman for this mex -> j -> i, we'll have this formula:
                    // with middleman mex -> j -> i: .... + cnt[j]*mex + cnt[i]*j
                    // without middleman mex -> i:   .... + cnt[i]*mex
                    // since cnt[i] < cnt[j] (because dp[j] = INF so it hasn't touch with v yet) so without middleman will be more optimized
                }
                dp[i] = query(v-1) + i; // cnt[i] - 1
            }
        }

        cout << dp[0] << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}