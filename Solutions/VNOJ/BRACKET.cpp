/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-18 21:45:09
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: BRACKET
 *    source: bedao_r14_bracket
 *    submission: https://oj.vnoi.info/submission/11905547
 *    status: AC
 * ----------------------------------------------------------
 *    tags: RMQ
 *    complexity: O(n \log n + q)
 *    note: Make the brackets to a prefix sum, close bracket = -1, open = +1. To get a valid [L;R], we need pref[R] - pref[L-1] = 0 => pref[R] = pref[L-1] AND pref[L-1] and pref[R] must be the lowest value in pref array in [L;R] because if there's a lower value, there's a negative number in that array, so we can't create a good bracket (means that there are more close brackets than open brackets at that part) => Let V = minimum value of pref in [l;r], pref[R] = pref[L-1] <= V. We know that on each consecutive index on the array, the pref value only change the value with the range of 1, so if you can find any pref[R] = pref[L-1] < V means that you can also find one = V. So to get R-l = min, we need to find pref[R] = pref[L-1] = V. Now we use array _pos_ to mark all pref value that had emergenced, now we find V by using sparse table, and then use lower_bound to search good index in pos[V] to get nearest L and R to l and r
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

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
    if(!fopen("BRACKET.INP", "r")) return;
    freopen("BRACKET.INP", "r", stdin);
    freopen("BRACKET.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int pref[N];
int st[N][19];
int lg[N];
vi pos[2*N];

// ----------------------- [ FUNCTIONS ] -----------------------
int get_min(int l, int r){
    int k = lg[r-l+1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int get_pos_left(int V, int x){
    int it = upper_bound(all(pos[V],0), x) - pos[V].begin() - 1;
    if(it < 0) return -1;
    return pos[V][it];
}

int get_pos_right(int V, int x){
    int it = lower_bound(all(pos[V],0), x) - pos[V].begin();
    if(it >= sz(pos[V])) return -1;
    return pos[V][it];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    string s;
    cin >> s;
    s = '#' + s;
    
    pos[0 + N].eb(0);
    st[0][0] = 0;
    for(int i = 1; i <= n; i++){
        pref[i] = pref[i-1] + (s[i] == '(' ? 1 : -1);
        st[i][0] = pref[i];
        pos[pref[i]+N].eb(i); // offset
    }
    for(int i = 2; i <= n; i++) lg[i] = lg[i>>1] + 1;
    for(int k = 1; k <= 18; k++){
        for(int i = 0; i + (1 << k) - 1  <= n; i++){
            st[i][k] = min(st[i][k-1], st[i + (1 << (k-1))][k-1]);
        }
    }

    while(q--){
        int l,r;
        cin >> l >> r;

        int V = get_min(l-1,r);
        V += N; // offset

        int L = get_pos_left(V, l-1);
        int R = get_pos_right(V, r);

        if(L != -1 && R != -1){
            cout << L+1 << ' ' << R << '\n'; // return L back to the right answer without the pref[L-1]
        }
        else cout << -1 << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}