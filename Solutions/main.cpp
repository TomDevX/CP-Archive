/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-03 21:13:09
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
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
#include <cstdio>
#include <utility>
#include <string>
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

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 20032024;

// ----------------------- [ FUNCTIONS ] -----------------------
bool is_nguyen(char c){
    return c == 'e' || c == 'u' || c == 'o' || c == 'a' || c == 'i';
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int tc;
    cin >> tc;
    while(tc--){
        string s;
        cin >> s;
        int n = sz(s);
        s = '#' + s;

        vi pref_cnt_nguyen(n+1);
        vi pref_cnt_phu(n+1);
        vi suff_cnt_nguyen(n+2);
        vi suff_cnt_phu(n+2);

        vi pref_idx_nguyen(n+1,-1);
        vi pref_idx_phu(n+1,-1);
        vi suff_idx_nguyen(n+2,-1);
        vi suff_idx_phu(n+2,-1);

        
        for(int i = 1; i <= n; i++){
            if(is_nguyen(s[i])){
                pref_cnt_nguyen[i]++;
                pref_idx_nguyen[i] = i;
            }
            else{
                pref_cnt_phu[i]++;
                pref_idx_phu[i] = i;
            }
            
            pref_cnt_nguyen[i] += pref_cnt_nguyen[i-1];
            pref_cnt_phu[i] += pref_cnt_phu[i-1];
            pref_idx_nguyen[i] = max(pref_idx_nguyen[i], pref_idx_nguyen[i-1]);
            pref_idx_phu[i] = max(pref_idx_phu[i], pref_idx_phu[i-1]);
        }
        
        for(int i = n; i >= 1; i--){
            if(is_nguyen(s[i])){
                suff_cnt_nguyen[i]++;
                suff_idx_nguyen[i] = i;
            }
            else{
                suff_cnt_phu[i]++;
                suff_idx_phu[i] = i;
            }
            
            suff_cnt_nguyen[i] += suff_cnt_nguyen[i+1];
            suff_cnt_phu[i] += suff_cnt_phu[i+1];
            suff_idx_nguyen[i] = max(suff_idx_nguyen[i], suff_idx_nguyen[i+1]);
            suff_idx_phu[i] = max(suff_idx_phu[i], suff_idx_phu[i+1]);
        }
        
        ll ans = 0;
        for(int i = 1; i <= n; i++){
            if(tc == 4){
                dbg(suff_idx_nguyen[i+1],i);
            }
            if(pref_idx_nguyen[i] == i && (suff_idx_phu[i+1] < suff_idx_nguyen[i+1] || suff_idx_nguyen[i+1] == -1) && suff_idx_phu[i+1] != -1){
                int pos = (suff_idx_nguyen[i+1] == -1 ? n : suff_idx_nguyen[i+1]-1);
                ans = (ans + pos - i)%MOD;
                dbg(pos,1);
            }
        }

        for(int i = n; i >= 1; i--){
            if(suff_idx_nguyen[i] == i && (pref_idx_phu[i-1] > pref_idx_nguyen[i-1] || pref_idx_nguyen[i-1] == -1) && pref_idx_phu[i-1] != -1){
                int pos = (pref_idx_nguyen[i-1] == -1 ? 1 : pref_idx_nguyen[i-1]+1);
                ans = (ans + i - pos)%MOD;
            }
        }

        cout << ans << '\n';
    }
}