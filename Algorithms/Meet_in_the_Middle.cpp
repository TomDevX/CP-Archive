#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>

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

// ----------------------- [ MAIN ] -----------------------
int main(){
    int n,s;
    cin >> n >> s;

    int mid = n>>1;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vi tot;
    tot.reserve(1 << mid);

    for(int mask = 0; mask < (1 << mid); mask++){
        int sum = 0;
        for(int j = mask; j > 0; j &= (j-1)){
            sum += a[__builtin_ctz(j)+1];
            if(sum > s) break;
        }   
        if(sum <= s) tot.eb(sum);
    }

    ll ans = 0;
    sort(all(tot,0));
    for(int mask = 0; mask < (1 << (n-mid)); mask++){
        int sum = 0;
        for(int j = mask; j > 0; j &= (j-1)){
            sum += a[__builtin_ctz(j)+1+mid];
            if(sum > s) break;
        }
        if(sum <= s){
            int it = lower_bound(all(tot,0), s-sum) - tot.begin();
            if(tot[it] == s-sum) ans += upper_bound(all(tot,0),s-sum) - tot.begin() - it;
        }
    }
    cout << ans;
}