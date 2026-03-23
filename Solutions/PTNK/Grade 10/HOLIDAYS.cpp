/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-08 09:39:41
 *    done in: <none>
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

const int N = 1e5+67;
vector<bool> vis(N);

struct box1{ // dinh duong
    int a,b,idx;

    bool operator<(const box1& other) const{
        if(a == other.a){
            if(b == other.b){
                return idx > other.idx;
            }
            return b < other.b;
        }
        return a < other.a;
    }
};

struct box2{ // do ngon
    int a,b,idx;

    bool operator<(const box2& other) const{
        if(b == other.b){
            if(a == other.a){
                return idx > other.idx;
            }
            return a < other.a;
        }
        return b < other.b;
    }
};

priority_queue<box1> pq1;
priority_queue<box2> pq2;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("HOLIDAYS.INP", "r", stdin);
    freopen("HOLIDAYS.OUT", "w", stdout);
}

int main(){
    fast();
    setup();
    
    int n;
    cin >> n;
    vector<pair<int,int>> vec(n+1);
    for(int i = 1; i <= n; i++){
        cin >> vec[i].first;
    }
    for(int i = 1; i <= n; i++){
        cin >> vec[i].second;
    }

    for(int i = 1; i <= n; i++){
        pq1.push({vec[i].first,vec[i].second,i});
        pq2.push({vec[i].first,vec[i].second,i});
    }

    int c;
    for(int i = 1; i <= n; i++){
        cin >> c;
        if(c == 1){
            box2 temp = pq2.top();
            while(vis[temp.idx]){
                pq2.pop();
                temp = pq2.top();
            }
            cout << temp.idx << ' ';
            vis[temp.idx] = true;
        }
        else{
            box1 temp = pq1.top();
            while(vis[temp.idx]){
                pq1.pop();
                temp = pq1.top();
            }
            cout << temp.idx << ' ';
            vis[temp.idx] = true;
        }
    }
}