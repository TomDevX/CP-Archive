/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-19 21:10:23
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Chuỗi con xuất hiện K lần
 *    source: https://oj.vnoi.info/problem/dtksub
 *    submission: https://oj.vnoi.info/submission/12341771
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash, Binary Search
 *    complexity: O(n \log n)
 *    note: We know that if f(len) = true (means that there's a substring with length of len appears at least k times) => f(len-1) = f(len-2) = ... = true. So we can binary search on that, but to check if 2 strings are the same fast, we hash them and put them in array, sort them and just count. (We dont use any map because it takes more time to access memory)
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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
    if(!fopen("dtksub.INP", "r")) return;
    freopen("dtksub.INP", "r", stdin);
    freopen("dtksub.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e4+5;

const ll MOD = 1234567891;
ll hashS[N], POW[N];
int a[N];
ll base = 31;
int n,k;
string s;

// ----------------------- [ FUNCTIONS ] -----------------------
void make_hash(){
    POW[0] = 1;
    for(int i = 1; i <= n; i++) POW[i] = (POW[i-1]*base)%MOD;

    for(int i = 1; i <= n; i++){
        hashS[i] = (hashS[i-1]*base + s[i] - 'a' + 1)%MOD;
    }
}

ll get(int l, int r){
    return ((hashS[r] - hashS[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

bool check(int len){
    for(int i = 1; i + len - 1 <= n; i++){
        a[i] = get(i, i + len - 1);
    }
    sort(sub(a,1,n-len+1));

    int cnt = 1;
    for(int i = 2; i <= n-len+1; i++){
        if(a[i] == a[i-1]) cnt++;
        else{
            if(cnt >= k){
                return true;
            }
            cnt = 1;
        }
    }
    return cnt >= k;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> k;
    cin >> s;

    s = '#' + s;

    make_hash();

    int l = 1, r = n-k+1, ans = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);

        if(check(mid)){
            l = mid+1;
            ans = mid;
        }
        else r = mid-1;

        dbg(mid,1);
    } 

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}