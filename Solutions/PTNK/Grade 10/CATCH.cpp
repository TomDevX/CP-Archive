/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-08 09:22:22
 *    done in: <none>
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;
int x,y;
vector<int> X = {0,0,0,1,-1,1,1,-1,-1};
vector<int> Y = {0,1,-1,0,0,1,-1,1,-1};

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("CATCH.INP", "r", stdin);
    freopen("CATCH.OUT", "w", stdout);
}

bool check(pair<int,int> &mouse){
    for(int i = 0; i < 9; i++){
        int newx = x+X[i];
        int newy = y+Y[i];
        if(mouse.first == newx && mouse.second == newy) return true;
    }
    return false;
}

int main(){
    fast();
    setup();
    
    bool ok = false;
    cin >> y >> x;
    string s;
    cin >> s;
    int n = s.size();
    s = '#' + s;
    pair<int,int> mouse = {0,0};
    if(check(mouse)){
        ok = true;
        cout << 0 << '\n';
    }
    for(int i = 1; i <= n; i++){
        if(s[i] == 'U') mouse.first++;
        else if(s[i] == 'D') mouse.first--;
        else if(s[i] == 'L') mouse.second--;
        else mouse.second++;

        if(check(mouse)){
            ok = true;
            cout << i << '\n';
        }
    }
    if(!ok) cout << -1;
}