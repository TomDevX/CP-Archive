constexpr int MAXN = 2e6 + 5;

// =================== [Multi Trie] =====================
struct TriePool {
    int child[MAXN][26];
    int cnt[MAXN];
    int exist[MAXN];
    int pool;
    int bin[MAXN];
    int tail;

    inline void reset() noexcept {
        pool = tail = 0;
        exist[0] = cnt[0] = 0;
        memset(child[0], -1, 26 * sizeof(int));
    }

    inline int alloc() noexcept {
        int id = (tail > 0) ? bin[--tail] : ++pool;
        exist[id] = cnt[id] = 0;
        memset(child[id], -1, 26 * sizeof(int));
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
            if (mem.child[u][c] == -1) mem.child[u][c] = mem.alloc();
            u = mem.child[u][c];
            mem.cnt[u]++;
        }
        mem.exist[u]++;
    }

    int find(const string& s) const noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (mem.child[u][c] == -1) return 0;
            u = mem.child[u][c];
        }
        return u;
    }

    void del(const string& s) noexcept {
        if (!mem.exist[find(s)]) return;
        int u = root;
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            int v = mem.child[u][c];
            mem.cnt[v]--;
            if (mem.cnt[v] == 0) {
                mem.child[u][c] = -1;
                int rem = v;
                for (int j = i + 1; j < s.size(); ++j) {
                    int child_rem = mem.child[rem][s[j] - 'a'];
                    mem.free(rem);
                    rem = child_rem;
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
    // 1. Đóng gói toàn bộ hạ tầng bộ nhớ vào nội bộ Struct
    int child[MAX_TRIE_NODES][26];
    int cnt[MAX_TRIE_NODES];
    int exist[MAX_TRIE_NODES];
    int bin[MAX_TRIE_NODES];
    int pool;
    int tail;
    
    int root;

    // 2. Hàm reset kho của riêng instance này
    void reset_pool() noexcept {
        pool = tail = 0;
        exist[0] = cnt[0] = 0;
        memset(child[0], -1, sizeof(child[0]));
    }

    // 3. Hàm cấp phát nội bộ
    int alloc() noexcept {
        int id = (tail > 0) ? bin[--tail] : ++pool;
        exist[id] = cnt[id] = 0;
        memset(child[id], -1, sizeof(child[id]));
        return id;
    }

    void free_node(int id) noexcept {
        bin[tail++] = id;
    }

    // 4. Các hàm thao tác logic gọi thẳng mảng nội bộ, không cần "mem." hay tiền tố gì cả
    void init() noexcept {
        root = alloc();
    }

    void add(const string& s) noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (child[u][c] == -1) child[u][c] = alloc();
            u = child[u][c];
            cnt[u]++;
        }
        exist[u]++;
    }

    int find(const string& s) const noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (child[u][c] == -1) return 0;
            u = child[u][c];
        }
        return u;
    }

    void del(const string& s) noexcept {
        int target = find(s);
        if (target == 0 || !exist[target]) return;

        int u = root;
        for (size_t i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            int v = child[u][c];
            cnt[v]--;
            if (cnt[v] == 0) {
                child[u][c] = -1;
                int rem = v;
                for (size_t j = i + 1; j < s.size(); ++j) {
                    int child_rem = child[rem][s[j] - 'a'];
                    free_node(rem);
                    rem = child_rem;
                }
                free_node(rem);
                return;
            }
            u = v;
        }
        exist[u]--;
    }
};