/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-10 07:35:45
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
#include <bitset>

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
    if(!fopen("Bai2.INP", "r")) return;
    freopen("Bai2.INP", "r", stdin);
    freopen("Bai2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int X[4] = {0,0,1,-1};
int Y[4] = {1,-1,0,0};
int n;
vvi a(11, vi(5));
pii cur = {0,0};
bitset<5> vis[11]; 

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= 4;
}

bool isRightPos(int x, int y){
    return a[x][y] == 4*(x-1) + y;
}

namespace sub2{
    int good = 0;
    bool isDone = false;
    vector<pair<pii,pii>> moves;

    bool check(){
        return n<= 3;
    }

    void backtrack(){
        if(isDone || good == 4*n){
            isDone = true;
            return;
        }
        if(vis[cur.fi][cur.se]) return;

        for(int k = 0; k < 4 && !isDone; k++){
            int newx = cur.fi + X[k];
            int newy = cur.se + Y[k];

            if(::check(newx,newy)){
                good -= isRightPos(newx,newy) + isRightPos(cur.fi,cur.se);
                swap(a[newx][newy], a[cur.fi][cur.se]);
                good += isRightPos(newx,newy) + isRightPos(cur.fi,cur.se);
                
                vis[cur.fi][cur.se] = 1;
                moves.eb(cur, make_pair(newx,newy));
                cur = {newx,newy};
                
                backtrack();
                dbg(good,k);
                if(isDone) return;
                
                good -= isRightPos(newx,newy) + isRightPos(cur.fi,cur.se);
                swap(a[newx][newy], a[cur.fi][cur.se]);
                good += isRightPos(newx,newy) + isRightPos(cur.fi,cur.se);
                
                vis[cur.fi][cur.se] = 0;
                cur = moves.back().fi;
                moves.pop_back();
            }
        }
    }

    void solve(){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= 4; j++){
                if(isRightPos(i,j)) good++;
            }
        }

        backtrack();
        cerr << "skibidi " << isDone << '\n';

        cout << sz(moves) << '\n';
        for(const pair<pii,pii>& p : moves){
            cout << p.fi.fi << ' ' << p.fi.se << ' ' << p.se.fi << ' ' << p.se.se << '\n';
        }
    }
}

namespace allsub{
    void solve(){
        vector<pair<pii,pii>> moves;
        while(cur.fi != n || cur.se != 4){
            bool moved = false;
            for(int k = 0; k < 4; k++){
                int newx = cur.fi + X[k];
                int newy = cur.se + Y[k];
                if(check(newx,newy) && a[newx][newy] == 4*(cur.fi-1) + cur.se){
                    moves.eb(make_pair(cur.fi,cur.se),make_pair(newx,newy));
                    swap(a[newx][newy], a[cur.fi][cur.se]);
                    cur = {newx,newy};
                    moved = true;
                    break;
                }
            }
            if(!moved) break;
        }

        cout << sz(moves) << '\n';
        
        for(const pair<pii,pii> &p : moves){
            cout << p.fi.fi << ' ' << p.fi.se << ' ' << p.se.fi << ' ' << p.se.se << '\n';
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 4; j++){
            cin >> a[i][j];
            if(a[i][j] == 4*n) cur = {i,j};
        }
    }

    if(sub2::check()) return sub2::solve(),0;
    return allsub::solve(),0;
    
    
    return NAH_I_WOULD_WIN;
}