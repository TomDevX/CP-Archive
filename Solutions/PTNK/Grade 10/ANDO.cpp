/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-12 11:21:06
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
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
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<long long>;

void setup(){
    if(!fopen("ANDO.INP", "r")) return;
    freopen("ANDO.INP", "r", stdin);
    freopen("ANDO.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+2;
int n;
bitset<N> not_good;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(all(a,1));

    int ans = 0;
    bool start = false;
    for(int i = 31; i >= 0; i--){
        int cnt = 0;
        // todo: reset start mỗi lần duyệt j
        for(int j = 1; j <= n; j++){
            if(!not_good[j] && (a[j] >> i)&1){
                start = true;
                cnt++;
            }
            else if(start == true){
                not_good[j] = 1;
            }
        }
        if(cnt >= 2){
            ans |= (1 << i);
        }
    }
    cout << ans;
}