#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <stack>
#include <queue>
#include <algorithm>
#include <cassert>
#include <ctype.h>
#include <math.h>
#include <iomanip>
#define int long long
#define ii pair<int,int>
#define fi first
#define se second
#define getbit(x,y) (((x)>>(y))&1)
#define turnon(x,y) ((x)|(1<<y))
#define turnof(x,y) ((x)^(1<<y))
#define oo 1000000000000000000
#define pb push_back
#define all(x) x.begin(),x.end()
#define con(mask) mask=(mask-1)&mask
#define Unique(val) val.erase(unique(val.begin(),val.end()),val.end())

const int mod=1e9+7;
using namespace std;

int n, m;

int par[100005];
int l[5005], r[5005];
string s[5005];

int Find(int u) {
    if(par[u] < 0) return u;
    return par[u] = Find(par[u]);
}

void join(int u, int v) {
    u = Find(u);
    v = Find(v);

    if(u != v) {
        if(par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
    }

    return;
}

signed main()
{

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    cin >> n >> m;

    vector<int>a;

    for(int i = 1; i <= m; i++) {
        cin >> l[i] >> r[i];
        a.pb(l[i] - 1);
        a.pb(r[i]);
        cin >> s[i];
    }

    sort(all(a));
    Unique(a);

    for(int i = 1; i <= 2 * n; i++) par[i] = -1;

    for(int i = 1; i <= n; i++) {
        // l[i] = lower_bound(all(a), l[i] - 1) - a.begin() + 1;
        // r[i] = lower_bound(all(a), r[i]) - a.begin() + 1;

        int x = l[i];
        int y = r[i] + 1;
        int doi_x = l[i] + n;
        int doi_y = r[i] + n + 1;
        if(i == 4) cerr << x << ' ' << y << ' ' << doi_x << ' ' << doi_y << '\n';

        x = Find(x);
        y = Find(y);
        doi_x = Find(doi_x);
        doi_y = Find(doi_y);

        if(i == 4) cerr << x << ' ' << y << ' ' << doi_x << ' ' << doi_y << '\n';

        if(s[i] == "odd") {
            //x va y không đồng dạng
            //=> nếu mà x cùng dạng với y hoặc doi_x cùng dạng với doi_y thì sẽ sai
            if(x == y || doi_x == doi_y) {
                cout << i - 1;
                return 0;
            }
            join(x, doi_y);
            join(y, doi_x);
        }
        else {
            //x và y đồng dạng
            //=> nếu x cùng dạng với doi_y hoặc y cùng dạng với doi_x thì sẽ sai
            if(x == doi_y || y == doi_x) {
                cout << i - 1;
                return 0;
            }
            join(x, y);
            join(doi_x, doi_y);
        }
    }

    cout << m;
    return 0;

    

    
}
//      ProTeam
//(¯`·.·´¯) (¯`·.·´¯)
//`·.¸(¯`·.·´¯)¸ .·
//×°× ` ·.¸.·´ ×°×
