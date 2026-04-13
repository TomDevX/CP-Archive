/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-11 01:25:19
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Prefix Sum Queries
 *    source: https://cses.fi/problemset/task/2166
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
#include <utility>
#include <cstring>

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
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
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
    if(!fopen("2166.INP", "r")) return;
    freopen("2166.INP", "r", stdin);
    freopen("2166.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int n;
int a[N];
ll pref[N];

ll st[4*N], t[4*N];
// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id] = pref[l];
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = max(st[lc], st[lc|1]);
}

void down(int id){

}

void update(int id, int l, int r, int pos, int val){
    if(l == r){
        t[id] += val;
        st[id] += val;
        return;
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(st,-0x3f,sizeof(st));
    
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        pref[i] = pref[i-1] + a[i];
    }

    build(1,1,n);

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int pos,val;
            cin >> pos >> val;
            update(1,1,n,pos,a[pos]-val);
            a[pos] = val;
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}