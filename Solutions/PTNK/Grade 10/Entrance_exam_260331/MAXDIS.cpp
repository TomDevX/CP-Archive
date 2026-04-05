/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-31 14:00:23
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Khoảng cách lớn nhất
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cmath>

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
    if(!fopen("MAXDIS.INP", "r")) return;
    freopen("MAXDIS.INP", "r", stdin);
    freopen("MAXDIS.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,l,r;
    cin >> n >> l >> r;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    sort(all(a,1));

    int ans = -2e9, maxdis = -1e9;

    if(r > a[n]){
        maxdis = r - a[n];
        ans = r;
    }

    for(int i = n-1; i >= 1; i--){
        int mid = ((a[i] + a[i+1])/2);
        if(mid > r || mid < l){
            if(r >= a[i] && r <= a[i+1] && min(abs(r - a[i]),abs(r - a[i+1])) > maxdis){
                maxdis = max(abs(r - a[i]),abs(r - a[i+1]));
                dbg(maxdis,i);
                ans = r;
            }
            if(l >= a[i] && l <= a[i+1] && min(abs(l - a[i]),abs(l - a[i+1])) > maxdis){
                maxdis = max(abs(l - a[i]),abs(l - a[i+1]));
                ans = l;
            }
        }
        else if(min(abs(mid - a[i]), abs(a[i+1] - mid)) > maxdis){
            maxdis = max(abs(mid - a[i]), abs(a[i+1] - mid));
            ans = mid;
        }
    }

    if(l < a[1] && a[1] - l > maxdis){
        maxdis = a[1] - l;
        ans = l;
    }

    cout << ans;

    return NAH_I_WOULD_WIN;
}