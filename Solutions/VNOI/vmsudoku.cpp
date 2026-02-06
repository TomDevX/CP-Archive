/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-06 16:23:49
 *    country: Vietnam - VNM
 *    title: VM 14 Bài 19 - Sudoku
 *    source: https://oj.vnoi.info/problem/vmsudoku
 *    submission: https://oj.vnoi.info/submission/11662085
 * ----------------------------------------------------------
 *    tags: constructive
 *    complexity: O(9^{21})
 *    note: I make a random valid sudoku board to increase the rate of getting a higher point and also do some little optimization so that it can do faster
**/

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
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
vii a(10,vi(10));
int hang[10], cot[10], block[10];

// vii res(10,vi(10));
ll ans = 0;
vector<pii> pos[10];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int sum[10];
int dis[10][10][10][10];
int can[10][10][9];

// ----------------------- [ FUNCTIONS ] -----------------------
int getblock(int x, int y){
    if(x <= 3){
        if(y <= 3) return 1;
        if(y <= 6) return 2;
        return 3;
    }
    if(x <= 6){
        if(y <= 3) return 4;
        if(y <= 6) return 5;
        return 6;
    }
    if(y <= 3) return 7;
    if(y <= 6) return 8;
    return 9;
}
void init(){
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            for(int u = 1; u <= 9; u++){
                for(int v = 1; v <= 9; v++){
                    dis[i][j][u][v] = abs(u-i)*abs(v-j);
                }
            }
        }
    }

    for(int x = 1; x <= 9; x++){
        for(int y = 1; y <= 9; y++){
            for(int i = 1; i <= 9; i++){
                can[x][y][i-1] = i;
            }
            shuffle(can[x][y], can[x][y]+9, rng);
        }
    }
}


void getpoint(){
    ll points = 0;
    for(int i = 1; i <= 9; i++){
        points += sum[i]*i;
    }
    points -= 17000;

    if(points > ans){
        ans = points;
        // res = a;
        for(int i = 1; i <= 9; i++){
            for(int j = 1; j <= 9; j++){
                cout << a[i][j];
            }
            cout << '\n';
        }
        dbg(ans,1);
    }
}

void backtrack(int x, int y){
    if(x > 9){
        getpoint();
        return;
    }
    if(y > 9){
        return backtrack(x+1,1);
    }

    if(a[x][y] > 0){
        return backtrack(x,y+1);
    }

    int cur_block = getblock(x, y);
    int mask = ~(hang[x] | cot[y] | block[cur_block]) & ((1 << 10) - 2);

    for (int i : can[x][y]) {
        if ((mask >> i) & 1) {
            hang[x] |= (1 << i);
            cot[y] |= (1 << i);
            block[cur_block] |= (1 << i);
            a[x][y] = i;

            int tmp = 0;
            for (pii &p : pos[i]) {
                tmp += dis[x][y][p.fi][p.se];
            }
            sum[i] += tmp;
            pos[i].eb(x, y);

            backtrack(x, y + 1);

            pos[i].pop_back();
            sum[i] -= tmp;
            a[x][y] = 0;
            hang[x] ^= (1 << i);
            cot[y] ^= (1 << i);
            block[cur_block] ^= (1 << i);
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    backtrack(1,1);

    // for(int i = 1; i <= 9; i++){
    //     for(int j = 1; j <= 9; j++){
    //         cout << res[i][j];
    //     }
    //     cout << '\n';
    // }
    // dbg(ans,1);
}