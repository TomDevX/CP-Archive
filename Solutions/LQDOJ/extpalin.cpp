/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-17 22:12:02
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tạo palindrome
 *    source: https://lqdoj.edu.vn/problem/extpalin
 *    submission: https://lqdoj.edu.vn/submission/8614762
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O(n)
 *    note: Just check for the best
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
    if(!fopen("extpalin.INP", "r")) return;
    freopen("extpalin.INP", "r", stdin);
    freopen("extpalin.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;

const ll MOD = 1234567891;
ll hashS[N], hashS_r[N], POW[N];
int base = 31;

string s,sR;


// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    POW[0] = 1;
    for(int i = 1; i < N; i++){
        POW[i] = (POW[i-1]*base)%MOD;
    }
}

void make_hash(){
    int n = sz(s)-1;
    for(int i = 1; i <= n; i++){
        hashS[i] = (hashS[i-1]*base + s[i] - 'a' + 1)%MOD;
    }

    for(int i = 1; i <= n; i++){
        hashS_r[i] = (hashS_r[i-1]*base + sR[i] - 'a' + 1)%MOD;
    }
}

ll get(int l, int r){
    return ((hashS[r] - hashS[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

ll getR(int l, int r){
    return ((hashS_r[r] - hashS_r[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

bool check(int x){
    int n = sz(s)-1;
    return get(n-x+1, n) == getR(1,x);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int tc;
    cin >> tc;
    while(tc--){
        cin >> s;
        int n = sz(s);

        sR = s;
        reverse(all(sR,0));
        s = "#" + s;
        sR = "#" + sR;

        make_hash();

        for(int i = n; i >= 1; i--){
            if(check(i)){
                s.erase(0,1);
                cout << s;
                for(int j = n-i-1; j >= 0; j--){
                    cout << s[j];
                }
                cout << '\n';

                break;
            }
        }

    }
    
    return NAH_I_WOULD_WIN;
}