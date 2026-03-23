#include <bits/stdc++.h>

using namespace std;

#define task "os"
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

struct node
{
    int val=0, lazy=0;
    node *l = nullptr, *r = nullptr;
};

int m,n;
node* root = new node;
int a[N+5], b[N+5];

void down(node* cur)
{
    if (!cur->lazy) return;
    if (!cur->l) cur->l = new node;
    cur->l->val = cur->l->lazy = cur->lazy;
    if (!cur->r) cur->r = new node;
    cur->r->val = cur->r->lazy = cur->lazy;
    cur->lazy = 0;
}

int upd(node*& cur, int l, int r, int u, int v, int val)
{
    //cout << l << ' ' << r << etr;
    if (v<l || u>r) return (cur ? cur->val : 0);
    if (!cur) cur = new node;
    if (u<=l && r<=v)
    {
        cur->val = val;
        cur->lazy = val;
        //cout << l << ' ' << r << ": " << val << etr;
        return cur->val;
    }

    down(cur);
    int mid = (l+r) >> 1;
    return cur->val = max(upd(cur->l, l, mid, u, v, val), upd(cur->r, mid+1, r, u, v, val));
}

int get(node* cur, int l, int r, int u, int v)
{
    if (v<l || u>r) return 0;
    if (!cur) return 0;

    //cout << l << ' ' << r << ": " << cur->val << etr;
    if (u<=l && r<=v) return cur->val;

    down(cur);
    int mid = (l+r) >> 1;
    return max(get(cur->l, l, mid, u, v), get(cur->r, mid+1, r, u, v));
}

void process()
{
	cin >> m >> n;
	for (int i=1; i<=n; i++)
    {
        cin >> a[i] >> b[i];
        upd(root, 1, m, a[i], b[i], i);
    }

    int cnt=0;
    for (int i=1; i<=n; i++)
    {
        cnt += (get(root, 1, m, a[i], b[i]) == i);
        //cout << get(root, 1, m, a[i], b[i]) << endl;
    }
    cout << cnt;
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