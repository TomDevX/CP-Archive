/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-26 14:11:01
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: STRINGKC
 *    source: BT_20260226.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
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
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("STRINGKC.INP", "r")) return;
    freopen("STRINGKC.INP", "r", stdin);
    freopen("STRINGKC.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;

    if(!(n&1)){
        cout << "No Solution";
        return 0;
    }

    string s;
    cin >> s;
    s = '#' + s;
    int mid = n>>1;

    bool cases[5] = {(s.substr(1,mid) == s.substr(mid+2,mid)), (s.substr(2,mid) == s.substr(mid+2,mid)), (s.substr(1,mid) == s.substr(mid+1,mid)), 1 ,1};


    // prev part
    bool used = false;
    int r = mid+2;
    for(int i = 1; i <= mid+1; i++){
        if(s[i] != s[r]){
            if(used){
                cases[3] = false;
                break;
            }
            used = true;
            r++;
            if(s[i] != s[r]){
                cases[3] = false;
                break;
            }
        }
        r++;
    }

    used = false;
    int l = 1;
    for(int i = mid+2; i <= n; i++){
        if(s[i] != s[l]){
            if(used){
                cases[4] = false;
                break;
            }
            used = true;
            l++;
            if(s[i] != s[l]){
                cases[4] = false;
                break;
            }
        }
        l++;
    }
    
    // 0: added middle
    // 1: added left
    // 2: added right
    // 3: added right part
    // 4: added left part
    vector<string> ans;
    if(cases[0]){
        ans.eb(s.substr(1,mid));
    }
    if(cases[2]){
        ans.eb(s.substr(1,mid));
    }
    if(cases[3]){
        ans.eb(s.substr(1,mid));
    }
    if(cases[1]){
        ans.eb(s.substr(2,mid));
    }
    if(cases[4]){
        ans.eb(s.substr(mid+2,mid));
    }

    if(sz(ans) == 0){
        cout << "No Solution";
        return 0;
    }
    sort(all(ans,0));
    for(int i = 1; i < sz(ans); i++){
        if(ans[i] != ans[i-1]){
            cout << "Multiple Solutions";
            return 0;
        }
    }
    cout << ans[0];

}