/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-23 09:51:52
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: JOB
 *    source: BT_20260223.pdf
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
#include <random>
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
    if(!fopen("JOB.INP", "r")) return;
    freopen("JOB.INP", "r", stdin);
    freopen("JOB.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ll> get_base(31,300);

int n,m;
const int N = 1002;
const ll MOD[2] = {(ll)1e9+6967, 1234567891};
char a[N][N];
ll hashA[2][N][N];
ll POW[2][N];
ll base = get_base(gen);

struct node{
    ll h1,h2;

    node(ll _h1 = 0, ll _h2 = 0) : h1(_h1), h2(_h2) {};
    
    bool operator<(const node& other) const{
        if(h1 != other.h1) return h1 < other.h1;
        return h2 < other.h2;
    }

    bool operator==(const node& other) const{
        return h1 == other.h1 && h2 == other.h2;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------
ll get_hash(int id, int j, int l, int r){
    ll res = (hashA[id][j][r] - hashA[id][j][l-1] * POW[id][r-l+1])%MOD[id];
    if (res < 0) res += MOD[id];
    return res;
}

void hash_init(){
    for(int id = 0; id < 2; id++){
        POW[id][0] = 1;
        for(int i = 1; i <= n; i++){
            POW[id][i] = (POW[id][i-1] * base)%MOD[id];
        }
    }

    for(int id = 0; id < 2; id++){
        for(int j = 1; j <= m; j++){
            for(int i = 1; i <= n; i++){
                hashA[id][j][i] = (hashA[id][j][i-1]*base + a[i][j] - 'a' + 1)%MOD[id];
            }
        }
    }
}

bool check(int mid){
    vector<node> trung(m+1);
    for(int i = 1; i <= m; i++){
        trung[i].h1 = get_hash(0,i,mid+1,n);
        trung[i].h2 = get_hash(1,i,mid+1,n);
    }

    sort(all(trung,1));

    for(int i = 1; i < m; i++){
        if(trung[i] == trung[i+1]) return false;
    }
    return true;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> m;
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }

    hash_init();

    int l = 0, r = n-1;
    int ans = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        if(check(mid)){
            ans = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
    cout << ans;
}