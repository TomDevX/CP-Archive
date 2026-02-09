/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-09 15:36:58
 *    country: Vietnam - VNM
 *    title: Số nguyên tố 1
 *    source: https://oj.vnoi.info/problem/c11prime
 *    submission: https://oj.vnoi.info/submission/11678299
 * ----------------------------------------------------------
 *    tags: Number Theory
 *    complexity: O(n^{1/4})
 *    note: In this code version we combine Pollard's Rho and Miller Rabin to test prime number. But there's a testcase which can break this code, so we need to use c11prime2's solution
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include <random>
#include <cmath>
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
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ull> disx(1,1e18), disc(1,1e18);
vector<ull> checkSet = {2,3,5,7,11,13,17,19,23,29,31,37};
ull ori_n;


// ----------------------- [ FUNCTIONS ] -----------------------
ull mul(ull a, ull b, ull MOD){
    ull res = 0;
    while(b){
        if(b&1){
            res = (res + a)%MOD;
        }
        a = (a+a)%MOD;
        b >>= 1;
    }
    return res;
}

ull binpow(ull a, ull b, ull MOD){
    ull res = 1;
    while(b){
        if(b&1){
            res = mul(res,a,MOD);
        }
        a = mul(a,a,MOD);
        b >>= 1;
    }
    return res;
}

bool test(ull a, ull n, ull m, int k){
    ull x = binpow(a,m,n);
    if(x == 1 || x == n-1) return true;
    for(int i = 1; i < k; i++){
        x = mul(x,x,n);
        if(x == n-1) return true;
    }
    return false;
}

bool MLRB(ull n){
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(!(n&1) || n % 3 == 0) return false;

    for(ull a : checkSet) if(n == a) return true;
    if(n < 41) return false;

    ull m = n-1, k = 0;
    while(!(m&1)){
        k++;
        m >>= 1;
    }

    for(int a : checkSet){
        if(!test(a,n,m,k)) return false;
    }
    return true;
}

ull g(ull x, ull c, ull MOD){
    return (mul(x,x,MOD) + c)%MOD;
}

bool check(ull m, ull &e){
    while(ori_n % m == 0){
        ori_n/=m;
        e++;
    }
    return ori_n == 1 && e > 1;
}

ull gcd(ull a, ull b){
    while(b){
        ull temp = a%b;
        a = b;
        b = temp;
    }
    return a;
}

ull ABS(ull a, ull b){
    if(a > b) return a-b;
    return b-a;
}

void PLR(ull n){
    dbg(n,1);
    if(n == 1) return;
    if(MLRB(n)){
        ull e = 0;
        if(check(n,e)){
            cout << n << ' ' << e;
        }
        else cout << 0;
        exit(0);
    }

    ull x = disx(gen), y = x;
    ull c = disc(gen);
    ull d = 1;
    
    while(d == 1){
        x = g(x,c,n);
        y = g(g(y,c,n),c,n);

        d = gcd(ABS(x,y),n);

        if(d == n){
            c = disc(gen);
            x = y = disx(gen);
        }
    }
    return PLR(d);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    ull n;
    cin >> n;
    if(n <= 2){
        cout << 0;
        return 0;
    }
    ori_n = n;
    disx.param(uniform_int_distribution<ull>::param_type(2,n-1));
    disc.param(uniform_int_distribution<ull>::param_type(1,n-1));

    PLR(n);

    cout << 0;
}