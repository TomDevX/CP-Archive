/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-02 09:27:18
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Matrix Exponentiation - Count path
 *    source: https://oj.vnoi.info/problem/errichto_matexp_cntpath
 *    submission: https://oj.vnoi.info/submission/11787099
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Matrix Exponentiation
 *    complexity: O(n^3 \cdot \log k)
 *    note: To count all the ways to move from a to b with middleman vertex (x), we count sum(ways[a -> x] * ways[b -> x]) with x = 1 -> n. We notice that it is the matrix exponentiation formula. At first, ways[a -> x] and ways[x -> b] only go through 1 edges, after doing the formula, every ways[a -> b] is 2 now. So if we power ways array k times, we have all ways[a -> b] will go through exactly k roads.
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
const ll MOD = 1e9+7;

// ----------------------- [ FUNCTIONS ] -----------------------
struct Matrix{
    int n,m;
    vvll mat;

    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m) {
        mat = vvll(n+1,vll(m+1));
    };

    static Matrix init(int n){
        Matrix res(n,n);
        for(int i = 1; i <= n; i++){
            res.mat[i][i] = 1;
        }

        return res;
    }

    Matrix operator*(const Matrix& b){
        Matrix res(n,b.m);

        for(int i = 1; i <= n; i++){
            for(int k = 1; k <= m; k++){
                if(mat[i][k] == 0) continue;
                for(int j = 1; j <= b.m; j++){
                    if(b.mat[k][j] == 0) continue;
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k]*b.mat[k][j]%MOD)%MOD;
                }
            }
        }

        return res;
    }

    Matrix operator^(int k){
        Matrix res = init(n);
        Matrix base = *this;

        while(k){
            if(k&1){
                res = res*base;
            }
            base = base*base;
            k >>= 1;
        }

        return res;
    }

    friend ostream& operator<<(ostream& os, const Matrix& base){
        for(int i = 1; i <= base.n; i++){
            for(int j = 1; j <= base.m; j++){
                os << base.mat[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }
};


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,m,k;
    cin >> n >> m >> k;

    Matrix a(n,n);
    
    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        a.mat[u][v]++;
    }

    Matrix res = a^k;
    ll ans = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            ans = (ans + res.mat[i][j])%MOD;
        }
    }
    cout << ans;
}