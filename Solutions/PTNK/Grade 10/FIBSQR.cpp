/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-16 15:41:21
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: FIBSQR
 *    source: BT_20260316.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Matrix Exponentiation
 *    complexity: O(\log n)
 *    note: We have a formula for dp that sum(fibo(1 -> n)^2) = fibo_n * fibo_{n+1}. Apply that formula we calculate fibo_n and fibo_{n+1} with matrix exponentiation
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
    if(!fopen("FIBSQR.INP", "r")) return;
    freopen("FIBSQR.INP", "r", stdin);
    freopen("FIBSQR.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 998244353;
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
    
    ll n;
    cin >> n;

    Matrix A(2,2);
    A.mat[1][1] = A.mat[1][2] = A.mat[2][1] = 1;
    
    Matrix V(2,1);
    V.mat[1][1] = 1;
    V.mat[2][1] = 1;

    Matrix fibo_n1 = (A^(n-1))*V;
    Matrix fibo_n = (A^n)*V;

    Matrix res = fibo_n*fibo_n1;

    cout << res.mat[1][1];
    
    return NAH_I_WOULD_WIN;
}