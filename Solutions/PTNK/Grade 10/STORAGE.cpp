/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-13 09:11:44
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: HỘP QUÀ
 *    source: BT_20260403
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sorting, Two Pointers
 *    complexity: O(n \log n)
 *    note: Sort and put the biggest possible box into another nearest biggest box
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
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
    if(!fopen("STORAGE.INP", "r")) return;
    freopen("STORAGE.INP", "r", stdin);
    freopen("STORAGE.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;
    ll sum = 0;

    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i], sum += a[i];

    sort(all(a,1));

    int r = n;
    for(int l = n-1; l >= 1; l--){
        if(a[l] + k <= a[r]){
            sum -= a[l];
            r--;
        }
    }

    cout << sum;
    
    return NAH_I_WOULD_WIN;
}