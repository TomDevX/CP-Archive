#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

long long dp[3001][20001];

struct figure{
    int w,v;
};

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    if(!fopen("ANIME.INP", "r")) return;
    freopen("ANIME.INP", "r", stdin);
    freopen("ANIME.OUT", "w", stdout);
}

int main(){
    fast();
    setup();

    memset(dp,0x3f,sizeof(dp));
    int lim = dp[1][1];
    dp[0][0] = 0;
    
    int n,W,H;
    cin >> n >> W >> H;
    int w,v,k;
    vector<figure> a = {{0,0}}; // force a.size()+1
    int tot_val = 0;

    for(int i = 1; i <= n; i++){
        cin >> w >> v >> k;
        tot_val += v*k;
        for(int j = 1; j <= k; j++){
            a.push_back({w,v});
        }
    }

    n = a.size()-1;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= tot_val; j++){
            dp[i][j] = dp[i-1][j];
            if(j >= a[i].v && dp[i-1][j-a[i].v] != lim){
                dp[i][j] = min(dp[i-1][j-a[i].v] + a[i].w,dp[i][j]);
            }
        }
    }

    for(int i = tot_val; i >= 0; i--){
        if(dp[n][i] <= W){
            cout << i;
            return 0;
        }
    }
}
