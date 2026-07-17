#include <bits/stdc++.h>

using namespace std;

#define task "ticket"
#define etr "\n"
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pli pair<long long,int>
#define pll pair<long long, long long>
#define fi first
#define se second
#define bg begin
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define lwb lower_bound
#define upb upper_bound
#define range(x, l, r) x+l, x+1+r
#define all(x) (x).bg(), (x).end()
#define compact(x) x.resize(unique(all(x)) - (x).bg())
#define sq(x) ((x)*(x))

void freop()
{
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w", stdout);
}

const int N=1e5, M=1e5, mod=1e9+7;

int n,m,k;
int seg[N*4+5], lazy[N*4+5];

void down(int id)
{
    if (!lazy[id]) return;
    seg[id*2] += lazy[id];
    seg[id*2+1] += lazy[id];
    lazy[id*2] += lazy[id];
    lazy[id*2+1] += lazy[id];

    lazy[id] = 0;
}

int upd(int id, int l, int r, int u, int v)
{
    if (v<l || u>r) return seg[id];
    if (u<=l && r<=v)
    {
        seg[id]++;
        lazy[id]++;
        return seg[id];
    }

    down(id);
    int mid = (l+r) >> 1;
    return seg[id] = max(upd(id*2, l, mid, u, v), upd(id*2+1, mid+1, r, u, v));
}

int get(int id, int l, int r, int u, int v)
{
    //cout << l << ' ' << r << ": " << seg[id] << etr;
    if (v<l || u>r) return 0;
    if (u<=l && r<=v) return seg[id];

    down(id);

    int mid = (l+r) >> 1;
    return max(get(id*2, l, mid, u, v), get(id*2+1, mid+1, r, u, v));
}

void process()
{
	cin >> n >> k >> m;
	while (m--)
    {
        int x,y;
        cin >> x >> y;
        //cout << get(1, 0, n-1, x, y-1) << ' ';
        if (get(1, 0, n-1, x, y-1) == k) cout << 0 << etr;
        else
        {
            upd(1, 0, n-1, x, y-1);
            cout << 1 << etr;
        }
    }

    //cout << get(1, 0, n-1, 0, 3) << etr;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freop();

	int t=1; //cin >> t;
	while (t--) process();

	return 0;
}
Beta
0 / 0
used queries
1