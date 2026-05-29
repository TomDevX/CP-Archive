constexpr int MAXN = 2e6 + 5;

// =================== [Multi Trie] =====================
struct TriePool {
    int nxt[MAXN][26];
    int cnt[MAXN];
    int exist[MAXN];
    int pool;
    int bin[MAXN];
    int tail;

    inline void reset() noexcept {
        pool = tail = 0;
        exist[0] = cnt[0] = 0;
        for(int i = 0; i < 26; i++) nxt[0][i] = -1;
    }

    inline int alloc() noexcept {
        int id = (tail > 0) ? bin[--tail] : ++pool;
        exist[id] = cnt[id] = 0;
        for(int i = 0; i < 26; i++) nxt[id][i] = -1;
        return id;
    }

    inline void free(int id) noexcept {
        bin[tail++] = id;
    }
};

TriePool mem;

struct Trie {

    int root;

    Trie() { root = 0; }

    void init() noexcept {
        root = mem.alloc();
    }

    void add(const string& s) noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (mem.nxt[u][c] == -1) mem.nxt[u][c] = mem.alloc();
            u = mem.nxt[u][c];
            mem.cnt[u]++;
        }
        mem.exist[u]++;
    }

    int find(const string& s) const noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (mem.nxt[u][c] == -1) return 0;
            u = mem.nxt[u][c];
        }
        return u;
    }

    void del(const string& s) noexcept {
        if (!mem.exist[find(s)]) return;
        int u = root;
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            int v = mem.nxt[u][c];
            mem.cnt[v]--;
            if (mem.cnt[v] == 0) {
                mem.nxt[u][c] = -1;
                int rem = v;
                for (int j = i + 1; j < s.size(); ++j) {
                    int nxt_rem = mem.nxt[rem][s[j] - 'a'];
                    mem.free(rem);
                    rem = nxt_rem;
                }
                mem.free(rem);
                return;
            }
            u = v;
        }
        mem.exist[u]--;
    }
};


// ================= [Single Trie] =================
struct Trie {
    int nxt[MAX_TRIE_NODES][26];
    int cnt[MAX_TRIE_NODES];
    int exist[MAX_TRIE_NODES];
    int bin[MAX_TRIE_NODES];
    int pool;
    int tail;
    
    int root;

    inline void reset_pool() noexcept {
        pool = tail = 0;
        exist[0] = cnt[0] = 0;
        for(int i = 0; i < 26; i++) nxt[0][i] = -1;
    }

    inline int alloc() noexcept {
        int id = (tail > 0) ? bin[--tail] : ++pool;
        exist[id] = cnt[id] = 0;
        for(int i = 0; i < 26; i++) nxt[id][i] = -1;
        return id;
    }

    inline void free_node(int id) noexcept {
        bin[tail++] = id;
    }

    void init() noexcept {
        root = alloc();
    }

    void add(const string& s) noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[u][c] == -1) nxt[u][c] = alloc();
            u = nxt[u][c];
            cnt[u]++;
        }
        exist[u]++;
    }

    int find(const string& s) const noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[u][c] == -1) return 0;
            u = nxt[u][c];
        }
        return u;
    }

    void del(const string& s) noexcept {
        int target = find(s);
        if (target == 0 || !exist[target]) return;

        int u = root;
        for (size_t i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            int v = nxt[u][c];
            cnt[v]--;
            if (cnt[v] == 0) {
                nxt[u][c] = -1;
                int rem = v;
                for (size_t j = i + 1; j < s.size(); ++j) {
                    int nxt_rem = nxt[rem][s[j] - 'a'];
                    free_node(rem);
                    rem = nxt_rem;
                }
                free_node(rem);
                return;
            }
            u = v;
        }
        exist[u]--;
    }
};