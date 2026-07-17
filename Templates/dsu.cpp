// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n){
    iota(par + 1, par + n + 1,1);
}

int root(int u){
    if(par[u] == u) return u;
    return par[u] = root(par[u]);
}

bool unite(int a, int b){
    a = root(a), b = root(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a,b);

    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;

    return true;
}

bool get(int a, int b){
    a = root(a), b = root(b);
    if(a == b) return true;
    return false;
}