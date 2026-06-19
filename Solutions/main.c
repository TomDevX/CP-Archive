#include <stdio.h>
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define N 200005
#define M 400005

struct Edge {
    int u, v, s;
};

int head[N], to_node[M], next_edge[M], edge_cnt;
struct Edge E[M];

int low[N], num[N], group[N];
bool del[N];
bool bad[M];
int cnt, scc;

int st[N], top;

void add_edge(int u, int v) {
    to_node[++edge_cnt] = v;
    next_edge[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void rest(int n, int m) {
    cnt = 0;
    scc = 0;
    top = 0;
    edge_cnt = 0;
    
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        low[i] = num[i] = group[i] = 0;
        del[i] = false;
    }
    for (int i = 1; i <= m; i++) {
        bad[i] = false;
    }
}

void tarjan(int u) {
    num[u] = low[u] = ++cnt;
    st[++top] = u;

    for (int e = head[u]; e; e = next_edge[e]) {
        int v = to_node[e];
        if (del[v]) continue;
        if (num[v] == 0) {
            tarjan(v);
            low[u] = MIN(low[u], low[v]);
        } else {
            low[u] = MIN(low[u], num[v]);
        }
    }

    if (low[u] == num[u]) {
        int v = 0;
        scc++;
        do {
            v = st[top--];
            del[v] = true;
            group[v] = scc;
        } while (v != u);
    }
}

void __TomDev() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return;
    
    rest(n, m);
    
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].s);
        add_edge(E[i].u, E[i].v);
    }

    for (int i = 1; i <= m; i++) {
        if (E[i].s == -1) {
            bad[i] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (num[i] == 0) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (E[i].s >= 1 && !bad[E[i].s] && group[E[i].u] == group[E[i].v]) {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
}

int main() {
    char buf[1 << 16];
    setvbuf(stdin, buf, _IOFBF, sizeof(buf));

    int tc = 1;
    scanf("%d", &tc);
    for (int t = 1; t <= tc; t++) {
        __TomDev();
    }
}
