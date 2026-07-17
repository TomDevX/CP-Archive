/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-25 22:35:42
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Missing Coin Sum Queries
 *    source: https://cses.fi/problemset/task/2184
 *    submission: https://cses.fi/problemset/result/16681741/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sparse Table, MEX, bit
 *    complexity: O(n \log n \log a_i)
 *    note: We have a proved trick that if we can create any value from 1 to S and currently processing x_i, if x_i <= S+1 -> every number in [1;S+x_i] always can be created by some numbers, if x_i > S+1 -> S+1 is the MEX. So now we group our array with their highest bit, represent if they are >= 2^k or not. Let x_i >= 2^k, if x_i <= S+1 => S+1 >= 2^k and S+x_i >= 2^{k+1}, so that we can add all the numbers that have their value in [2^k; 2^{k+1} - 1]. So the array pref below, we store prefix sum of elements that are >= 2^k and < 2^{k+1} by examining their bits. The st array is the sparse table which stores the min value which is in [2^k; 2^{k+1} - 1] in a range, so if that min value satisfies the condition min_val <= S+1, so the whole values in [2^k; 2^{k+1} - 1] will satisfies too so we add their sum in our current sum.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cmath>
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
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
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
    if(!fopen("2184.INP", "r")) return;
    freopen("2184.INP", "r", stdin);
    freopen("2184.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
ll pref[N][30];
int st[30][18][N], lg[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    for(int i = 2; i < N; i++) lg[i] = lg[i>>1] + 1;
    memset(st,0x3f,sizeof(st));
}

int get(int l, int r, int bit){
    int k = lg[r-l+1];
    return min(st[bit][k][l], st[bit][k][r - (1 << k) + 1]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,q;
    cin >> n >> q;

    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        st[(int)log2(a[i])][0][i] = a[i];
    }

    for(int i = 1; i <= n; i++){
        for(int k = 0; k <= 29; k++){
            pref[i][k] = pref[i-1][k] + ((int)log2(a[i]) == k ? a[i] : 0);
        }
    }

    for(int k = 1; k <= 17; k++){
        for(int j = 0; j <= 29; j++){
            for(int i = 1; i + (1 << k) - 1 <= n; i++){
                st[j][k][i] = min(st[j][k-1][i], st[j][k-1][i + (1 << (k-1))]);
            }
        }
    }

    while(q--){
        int l,r;
        cin >> l >> r;

        ll sum = 0;
        for(int k = 0; k <= 29; k++){ // we need to use for instead of while because if the current value is empty, it will return INF and we get a false answer, to we just continue interate all the 2^k
            if(get(l,r,k) <= sum+1){
                sum += pref[r][k] - pref[l-1][k];
            }
        }

        cout << sum + 1 << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}