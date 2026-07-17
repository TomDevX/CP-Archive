/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-23 09:00:08
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Schedule Management
 *    source: https://codeforces.com/contest/1701/problem/C
 *    submission: https://codeforces.com/contest/1701/submission/375702782
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Binary Search, Math
 *    complexity: O(n \log m)
 *    note: Just basically binary search answer on time. We need to prioritize the assigned worker first, if their tasks <= time, we will bring him to make more (time - cnt[i])/2 tasks after doing all his cnt[i] tasks, if tasks > time, we need more tasks to be done (cnt[i] - time).
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("1701C.INP", "r")) return;
    freopen("1701C.INP", "r", stdin);
    freopen("1701C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int cnt[N];
int n,m;

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int time){
    ll tasks = 0;
    for(int i = 1; i <= n; i++){
        if(cnt[i] <= time){
            tasks += ((time - cnt[i])>>1);
        }
        else{
            tasks -= cnt[i] - time;
        }
    }

    return tasks >= 0;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n >> m;

        memset(cnt,0,sizeof(cnt[0])*(n+1));

        for(int i = 1; i <= m; i++){
            int x;
            cin >> x;
            cnt[x]++;
        }

        int l = 1, r = m<<1, ans = 0;
        while(l <= r){
            int t = l + ((r-l)>>1);

            if(check(t)){
                r = t-1;
                ans = t;
            }
            else l = t+1;
        }

        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}