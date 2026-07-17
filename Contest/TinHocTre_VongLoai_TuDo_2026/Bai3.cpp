/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-10 07:35:47
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Thong diep
 *    source: https://tinhoctre.vn/problem/26vlqg2_message
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
    if(!fopen("Bai3.INP", "r")) return;
    freopen("Bai3.INP", "r", stdin);
    freopen("Bai3.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2005;

ll MOD[2] = {1234567891, (int)1e9+6967};
ll hashA[2][N], hashB[2][N], hashC[2][N], POW[2][N];

ll base = 31;

// ----------------------- [ FUNCTIONS ] -----------------------
ll get_hashA(int id, int l, int r){
    return ((hashA[id][r] - hashA[id][l-1]*POW[id][r-l+1])%MOD[id] + MOD[id])%MOD[id];
}

ll get_hashB(int id, int l, int r){
    return ((hashB[id][r] - hashB[id][l-1]*POW[id][r-l+1])%MOD[id] + MOD[id])%MOD[id];
}

ll get_hashC(int id, int l, int r){
    return ((hashC[id][r] - hashC[id][l-1]*POW[id][r-l+1])%MOD[id] + MOD[id])%MOD[id];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    string a,b,c;
    cin >> a >> b >> c;
    a = '#' + a;
    b = '#' + b;
    c = '#' + c;

    POW[0][0] = POW[1][0] = 1;
    for(int id = 0; id < 2; id++){
        for(int i = 1; i <= n; i++){
            POW[id][i] = (POW[id][i-1]*base)%MOD[id];
        }
    }

    for(int id = 0; id < 2; id++){
        for(int i = 1; i <= n; i++){
            hashA[id][i] = (hashA[id][i-1]*base + a[i] - 'a' + 1)%MOD[id];
        }
    }

    for(int id = 0; id < 2; id++){
        for(int i = 1; i <= n; i++){
            hashB[id][i] = (hashB[id][i-1]*base + b[i] - 'a' + 1)%MOD[id];
        }
    }

    for(int id = 0; id < 2; id++){
        for(int i = 1; i <= n; i++){
            hashC[id][i] = (hashC[id][i-1]*base + c[i] - 'a' + 1)%MOD[id];
        }
    }

    // process A
    pii AA = {0,-1}, BA = {0,-1};
    for(int Al = 1; Al <= n; Al++){
        for(int Br = n; Br >= 1; Br--){
            int Ar = Al, Bl = Br;
            while(get_hashA(0,Al,Ar) == get_hashB(0,Bl,Br) && get_hashA(1,Al,Ar) == get_hashB(1,Bl,Br)){
                Ar++;
                Bl--;
            }
            Ar--, Bl++;
            if(Ar < Al) continue;
            if(Ar - Al + 1 > AA.se - AA.fi + 1){
                AA = {Al,Ar};
                BA = {Bl,Br};
                Br = Bl;
                Al = Ar;
            }
        }
    }

    dbg(AA,BA);

    // process B
    pii AB = {0,-1}, CB = {0,-1};
    for(int Ar = n; Ar >= max(0,AA.se) + 1; Ar--){
        for(int Cl = 1; Cl <= n; Cl++){
            int Al = Ar, Cr = Cl;
            while(get_hashA(0,Al,Ar) == get_hashB(0,Cl,Cr) && get_hashA(1,Al,Ar) == get_hashB(1,Cl,Cr)){
                Al--;
                Cr++;
            }
            Al++, Cr--;
            cerr << "skibidi2\n";
            if(Ar < Al) continue;
            if(Ar - Al + 1 > AB.se - AB.fi + 1){
                AB = {Al,Ar};
                CB = {Cl,Cr};
                Cl = Cr;
                Al = Ar;
                cerr << "skibidi\n";
            }
        }
    }

    dbg(AB,CB);
    
    return NAH_I_WOULD_WIN;
}