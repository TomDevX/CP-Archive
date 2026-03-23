/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-19 10:46:27
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: rmq_divseq
 *    source: https://oj.vnoi.info/problem/rmq_divseq
 *    submission: https://oj.vnoi.info/src/11908097
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sparse Table
 *    complexity: O(n \log n)
 *    note: We need to know the safe pos before i to make a good array from [pos;i], so we make it both ways prefix (array L) and suffix (array R). The answer will get the intersect of that pos with prefix and suffix
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
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
    if(!fopen("rmq_divseq.INP", "r")) return;
    freopen("rmq_divseq.INP", "r", stdin);
    freopen("rmq_divseq.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+2;
int last[N], L[N], R[N], lg[N];
int st_min[N][20], st_max[N][20];

// ----------------------- [ FUNCTIONS ] -----------------------
int get_min(int l, int r){
    int k = lg[r-l+1];
    return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
}
int get_max(int l, int r){
    int k = lg[r-l+1];
    return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    vi sorted = a;
    sort(all(sorted,1));
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(all(sorted,1),a[i]) - sorted.begin();
    }

    for(int i = 2; i <= n; i++){
        lg[i] = lg[i>>1] + 1;
    }

    for(int i = 1; i <= n; i++){
        st_max[i][0] = last[a[i]];
        last[a[i]] = i;
    }

    memset(last,0,sizeof(last));

    for(int i = n; i >= 1; i--){
        if(last[a[i]] == 0){
            st_min[i][0] = n+1;
        }
        else st_min[i][0] = last[a[i]];
        last[a[i]] = i;
    }

    for(int k = 1; k <= 19; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st_min[i][k] = min(st_min[i][k-1], st_min[i + (1 << (k-1))][k-1]);
            st_max[i][k] = max(st_max[i][k-1], st_max[i + (1 << (k-1))][k-1]);
        }
    }

    int pos = 1;
    for(int i = 1; i <= n; i++){
        while(get_max(pos,i) >= pos){
            pos++;
        }
        L[i] = pos;
    }

    pos = n;

    for(int i = n; i >= 1; i--){
        while(pos > i && get_min(i,pos) <= pos) pos--;
        R[i] = pos;
    }

    while(q--){
        int l,r;
        cin >> l >> r;

        int posL = max(l, L[r] - 1);
        int posR = min(r - 1, R[l]);

        cout << max(0, posR - posL + 1) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}