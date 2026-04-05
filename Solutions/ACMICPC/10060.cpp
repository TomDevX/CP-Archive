/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-29 21:06:33
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Surveillance
 *    source: https://www.acmicpc.net/problem/10060
 *    submission: https://www.acmicpc.net/source/104478955
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sparse Table, Binary Lifting, Circle Problems
 *    complexity: O(n \log n)
 *    note: This sparse table problem is like a DP. First we need to double the array (which is the most optimal way to solve the complex circle problems) - we call this array A. Let up[u][k] = max index on array A after using 2^k cameras. Notice for the building below in the comment of the code. To get the result, we binary lifting with starting index from range [1;L].
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

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
    if(!fopen("10060.INP", "r")) return;
    freopen("10060.INP", "r", stdin);
    freopen("10060.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int L,n;
const int N = 1e6+2, LMAX = 2e6+2;
int up[LMAX][22], cnt[N], last[LMAX];
pii a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void addPhu(int l, int r){
    cnt[l]++;
    cnt[r+1]--;
}

void addPhuCirc(int l, int r){
    addPhu(l,L);
    addPhu(1,r);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> L >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i].fi >> a[i].se;
        if(a[i].fi > a[i].se){
            addPhuCirc(a[i].fi, a[i].se); // these check the "impossible" answer
            a[i].se += L;
        }
        else{
            addPhu(a[i].fi, a[i].se);
        }
        last[a[i].fi] = max(last[a[i].fi], a[i].se);
    }

    for(int i = 1; i <= L; i++){
        cnt[i] += cnt[i-1]; // this combine the diff array to see if there's a point that no cameras can view
        if(cnt[i] == 0){
            cout << "impossible";
            return 0;
        }
    }

    for(int i = 1; i <= 2*L; i++){
        if(last[i-1] >= i) last[i] = max(last[i], last[i-1]); // remember this important last[i-1] >= i check because we've doubled the array so there will be some points that doesn't have any camera
        up[i][0] = last[i];
    }

    for(int k = 1; k <= 21; k++){
        for(int i = 1; i <= 2*L; i++){
            if(up[i][k-1] != 0) up[i][k] = up[up[i][k-1] + 1][k-1]; // notice the unavailable positions, we check if up[i][k-1] is valid
            // also there's a up[i][k-1] + 1 because if we use that rope, we also include up[i][k-1] + 1 in that rope, so we + 1 to it to increase the range
        }
    }

    int ans = n;
    for(int i = 1; i <= L; i++){
        int u = i;
        int used = 0;
        for(int k = 21; k >= 0; k--){
            if(up[u][k] == 0) continue; // check if pos is valid
            if(up[u][k] < i + L){ // we check this because if the camera is out of range (L positions), there must be a way to less cameras but can still reach the whole circle
                u = up[u][k] + 1;
                used += (1 << k);
            }
        }
        if(u >= i + L) ans = min(ans, used); // if our current pos is equal to our endpoint of circle, we update it to the answer
    }
    // here you may wonder if our rope can reach out of the range i + L, why don't we update it -> when we iterate through all i, our missed previous positions will get in its position to fit the i + L
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}