// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n){
    iota(par + 1, par + n + 1,1);
}

int find_set(int u){
    if(par[u] == u) return u;
    return par[u] = find_set(par[u]);
}

bool union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return true;

    if(sz[a] < sz[b]) swap(a,b);

    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;

    return false;
}

bool get(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return true;
    return false;
}