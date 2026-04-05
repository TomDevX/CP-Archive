/**

 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-05 11:19:56
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: MEDIAN QUERY
 *    source: https://lqdoj.edu.vn/problem/trungvique
 *    submission: https://lqdoj.edu.vn/submission/8354746
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Mo's Algorithm, Sqrt Decomposition
 *    complexity: O(n \sqrt{q} + q \sqrt{q})
 *    note: We use Mo for the query and O(1) update for each move l,r in query. cnt[i] = number of occurences of value i in a[l -> r], block[i] = sum(cnt[i*BLOCK_SIZE -> (i+1)*BLOCK_SIZE - 1]). After updating, we query by getting the value that is higher than (r-l+1)/2 values
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int BLOCK_SIZE = 1000;
const int N = 1e5+2;
int cnt[N], block[BLOCK_SIZE];
struct Query{
    int l,r,id,blk;

    Query(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {};
    bool operator<(const Query& other) const{
        if(blk != other.blk) return blk < other.blk;

        if(blk&1) return r < other.r;
        return r > other.r;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    int q;
    cin >> q;
    vector<Query> queries(q+1);
    for(int i = 1; i <= q; i++){
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
        queries[i].blk = queries[i].l/BLOCK_SIZE;
    }
    sort(all(queries,1));

    int l = 1, r = 0;
    vi ans(q+1);
    for(int i = 1; i <= q; i++){
        while(r < queries[i].r){
            r++;
            cnt[a[r]]++;
            block[a[r]/BLOCK_SIZE]++;
        }
        while(r > queries[i].r){
            cnt[a[r]]--;
            block[a[r]/BLOCK_SIZE]--;
            r--;
        }
        while(l < queries[i].l){
            cnt[a[l]]--;
            block[a[l]/BLOCK_SIZE]--;
            l++;
        }
        while(l > queries[i].l){
            l--;
            cnt[a[l]]++;
            block[a[l]/BLOCK_SIZE]++;
        }

        int k = (queries[i].r-queries[i].l+2)/2;

        int cur_block = 0;
        while(k > block[cur_block]){
            k -= block[cur_block];
            cur_block++;
        }

        int cur = cur_block*BLOCK_SIZE;
        while(k > cnt[cur]){
            k -= cnt[cur];
            cur++;
        }

        ans[queries[i].id] = cur;
    }

    for(int i = 1; i <= q; i++){
        cout << ans[i] << '\n';
    }

    return NAH_I_WOULD_WIN;
}
