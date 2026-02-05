/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-08-09 23:59:20
 *    country: Vietnam - VNM
 *    title: Counting Rooms
 *    source: https://cses.fi/problemset/task/1192/
 *    submission: https://cses.fi/paste/96f91e45fb63bc5dd6975e/
 * ----------------------------------------------------------
 *    tags: BFS, flood fill
 *    complexity: O(V+E)
 *    note: 
 **/
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <cstring>
#include <bitset>
#include <queue>
 
#define all(x) x.begin(),x.end()
 
using namespace std;
 
vector<vector<bool>> vis(1e4+1,vector<bool>(1e4+1));
vector<int> X = {0,0,-1,1};
vector<int> Y = {1,-1,0,0};
int n,m;
 
void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
 
void setup(){
    freopen("BAI.INP", "r", stdin);
    freopen("BAI.OUT", "w", stdout);
}
 
bool check(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}
 
void bfs(int i, int j, vector<string> &a){
    vis[i][j] = true;
    queue<pair<int,int>> qu;
    qu.push({i,j});
    while(!qu.empty()){
        int x = qu.front().first;
        int y = qu.front().second;
        qu.pop();
        for(int k = 0; k < 4; k++){
            int newx = x+X[k];
            int newy = y+Y[k];
            if(check(newx,newy) && !vis[newx][newy] && a[newx][newy] == '.'){
                qu.push({newx,newy});
                vis[newx][newy] = true;
            }
        }
    }
}
 
int main(){
    fast();
    //setup();
 
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
 
    int res = 0;
    for(int i = 0; i < n; i++){
        for(int j= 0; j < m; j++){
            if(a[i][j] == '.' && !vis[i][j]){
                bfs(i,j,a);
                res++;
            }
        }
    }
    cout << res;
}