/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-29 08:23:46
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: NGHỈ NGƠI CHẤT LƯỢNG
 *    source: DT 29-06-2026.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n)
 *    metacognition: Check all cases
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
    #define dbg(x) cerr << "L" << __LINE__ << ": " << #x << " = " << (x) << '\n'
#else
    #define dbg(x)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("repose.INP", "r")) return;
    freopen("repose.INP", "r", stdin);
    freopen("repose.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

int ans[N], suff[N];
int n,q;
string s;
int cnt_on = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void precalc(){
    for(int i = 1; i <= n; i++){
        if(i < n && s[i] == '1' && s[i+1] == '1'){
            if(s[i-1] == '0') ans[0] += 2;
            else ans[0]++;
        }
        if(s[i] == '0') cnt_on++;
    }

    if(cnt_on == n){
        ans[0] = ans[1] = 0;
        for(int i = 2; i <= n; i++){
            ans[i] = i;
        }
        return;
    }

    vi pos;
    for(int i = 1; i <= n; i++){
        if(s[i] == '1' && s[i-1] == '0' && s[i+1] == '0'){
            pos.eb(i);
        }
    }
    int need = sz(pos);
    pos.eb(1e9);

    int bonus = 0;
    for(int i = 0; i < need; i++){
        if(pos[i] + 2 == pos[i+1]){
            ans[bonus+1] = ans[bonus] + 3;
            i++;
            s[pos[i] + 1] = '1';
            bonus++;
        }
    }

    for(int i = 0; i < need; i++){
        if(pos[i] + 2 == pos[i+1]){
            i++;
            continue;
        }
        if(pos[i] == n){
            ans[bonus+1] = ans[bonus] + 2;
            s[pos[i]-1] = '1';
        }
        else{
            ans[bonus+1] = ans[bonus] + 2;
            s[pos[i] + 1] = '1';
        }
        bonus++;
    }

    for(int i = bonus+1; i <= n; i++){
        ans[i] = ans[i-1] + 1;
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> q;
    cin >> s;
    s = '0' + s + '0';

    precalc();

    while(q--){
        int x;
        cin >> x;
        if(x > cnt_on) x = cnt_on;
        cout << ans[x] << '\n';
    }
}

int main(){
    fastio;
    setup();

    int tc = 1;
    // cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}