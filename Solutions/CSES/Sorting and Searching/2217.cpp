/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-10 10:12:02
 *    country: Vietnam - VNM
 *    title: Collecting Numbers II
 *    source: https://cses.fi/problemset/task/2217
 *    submission: https://cses.fi/problemset/result/16218382/
 * ----------------------------------------------------------
 *    tags: Adhoc
 *    complexity: O(n + m)
 *    note: We only switch once each time, and each of the switch only affect to the elements which have the adjacent value with the current one. So on each swap, we remove those 2 elements' effects, then swap them, and calculate their effects again
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int cnt[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n, q;
    cin >> n >> q;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        cnt[a[i]] = i; // save the indices of the element
    }

    int cur = 1;
    for(int i = 2; i <= n; i++){
        if(cnt[i] < cnt[i-1]) cur++; // calculate the initial differences
    }

    while(q--){
        int x,y;
        cin >> x >> y;
        if(a[x] > a[y]) swap(x,y); // it will be easier to process if we fix a[x] < a[y]

        // calculate their previous effect to the adjacent elements
        int truocx = (a[x] == 1 ? 0 : cnt[a[x]-1] > cnt[a[x]]); // before effect of x
        int saux = (a[x] == n ? 0 : cnt[a[x]+1] < cnt[a[x]]); // after effect of x
        int truocy = (a[y] == 1 ? 0 : cnt[a[y]-1] > cnt[a[y]]); // before effect of y
        int sauy = (a[y] == n ? 0 : cnt[a[y]+1] < cnt[a[y]]); // after effect of y

        if(a[y] - a[x] == 1){
            cur -= truocx + sauy + ((saux + truocy)>>1); // we must divide the effect by 2 because if those elements are adjacent so the smaller's after effect vs the bigger's before effect will be counted twice
        }
        else cur -= truocx + saux + truocy + sauy;

        // swap them
        cnt[a[x]] = y;
        cnt[a[y]] = x;
        swap(a[x],a[y]);
        swap(x,y); // to ensure that a[x] always < a[y]

        // calculate their current effect to the adjacent elements
        truocx = (a[x] == 1 ? 0 : cnt[a[x]-1] > cnt[a[x]]);
        saux = (a[x] == n ? 0 : cnt[a[x]+1] < cnt[a[x]]);
        truocy = (a[y] == 1 ? 0 : cnt[a[y]-1] > cnt[a[y]]);
        sauy = (a[y] == n ? 0 : cnt[a[y]+1] < cnt[a[y]]);
        if(a[y] - a[x] == 1){
            cur += truocx + sauy + ((saux + truocy)>>1);
        }
        else cur += truocx + saux + truocy + sauy;

        cout << cur << '\n';
    }
}