/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-16 22:24:41
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
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
    if(!fopen("test.INP", "r")) return;
    freopen("test.INP", "r", stdin);
    freopen("test.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;

int a[N];
int n,k,s;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n >> k >> s;

        for(int i = 1; i <= n; i++) cin >> a[i];

        int ans = 0, groups = 0;
        bool prev_err = false;
        ll sum_good = 0;

        for(int i = 1; i <= n; i++){
            if(k - groups == 1){
                if(sum_good) ans++;
                ll sum = 0;
                for(int j = i; j <= n; j++){
                    sum += a[j];
                }
                if(sum <= s){
                    ans++;
                }
                break;
            }

            if(sum_good + a[i] <= s){
                sum_good += a[i];
                prev_err = false;
                continue;   
            }
            else{
                if(sum_good){
                    ans++;
                    groups++;
                    sum_good = 0;
                    if(a[i] > s){
                        i--;
                        break;
                    }
                }
                else{
                    if(prev_err) continue;
                    prev_err = true;
                    groups++;
                }
            }
        }

        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}