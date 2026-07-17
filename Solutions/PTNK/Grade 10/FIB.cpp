/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-16 09:39:38
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: FIB
 *    source: BT_20260316.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Matrix Exponentiation
 *    complexity: O(\log R + \log L)
 *    note: We have sum from fibo(1 -> n) = fibo(n+2) - 1, apply that formula into our problem with matrix exponentiation
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
    if(!fopen("FIB.INP", "r")) return;
    freopen("FIB.INP", "r", stdin);
    freopen("FIB.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
ll MOD;
struct Matrix{
    int n,m;
    vvll mat;

    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m){
        mat = vvll(n+1,vll(m+1));
    }

    Matrix init(){
        Matrix res(n,m);
        for(int i = 1; i <= n; i++){
            res.mat[i][i] = 1;
        }
        return res;
    }

    Matrix operator*(Matrix b){
        Matrix res(n, b.m);
        for(int i = 1; i <= n; i++){
            for(int k = 1; k <= m; k++){
                for(int j = 1; j <= b.m; j++){
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k]*b.mat[k][j])%MOD;
                }
            }
        }
        return res;
    }

    Matrix operator^(ll k){
        Matrix res(n,m);
        res = init();
        if(k <= 0) return res;
        Matrix a = *this;

        while(k){
            if(k&1){
                res = res*a;
            }
            a = a*a;
            k >>= 1;
        }
        return res;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int a,b;
        ll l,r;
        ll m;
        cin >> a >> b >> l >> r >> m;

        MOD = m;

        Matrix A(2,2);
        A.mat[1][1] = A.mat[1][2] = A.mat[2][1] = 1;
        
        Matrix V(2,1);
        V.mat[1][1] = b%MOD;
        V.mat[2][1] = a%MOD;

        Matrix resR = (A^r)*V;
        Matrix resL = (A^(l-1))*V;

        cout << ((resR.mat[1][1]-1) - (resL.mat[1][1]-1) + MOD)%MOD << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}