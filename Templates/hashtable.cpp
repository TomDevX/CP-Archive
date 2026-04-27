struct HashTable {
    static const int MOD = 1000003; // Nên là số nguyên tố lớn
    static const int MAXN = 200005; // Số lượng phần tử tối đa sẽ chèn

    int head[MOD];      // Lưu chỉ số phần tử đầu tiên của mỗi bucket
    int nxt[MAXN];      // Trỏ đến phần tử tiếp theo trong chuỗi xung đột
    long long key[MAXN]; // Lưu khóa thực tế
    int val[MAXN];      // Lưu giá trị tương ứng
    int sz;             // Đếm số lượng phần tử hiện tại

    HashTable() {
        memset(head, 0, sizeof(head));
        sz = 0;
    }

    // Reset bảng băm (nhanh hơn memset toàn bộ nếu sz nhỏ)
    void clear() {
        for (int i = 1; i <= sz; ++i) {
            int h = (key[i] % MOD + MOD) % MOD;
            head[h] = 0;
        }
        sz = 0;
    }

    // Thêm hoặc cập nhật phần tử
    void insert(long long k, int v) {
        int h = (k % MOD + MOD) % MOD;
        // Kiểm tra xem đã tồn tại chưa
        for (int i = head[h]; i; i = nxt[i]) {
            if (key[i] == k) {
                val[i] = v; // Cập nhật nếu đã có
                return;
            }
        }
        // Chèn mới vào đầu danh sách liên kết của bucket h
        sz++;
        key[sz] = k;
        val[sz] = v;
        nxt[sz] = head[h];
        head[h] = sz;
    }

    // Lấy giá trị theo khóa (trả về -1 nếu không thấy)
    int get(long long k) {
        int h = (k % MOD + MOD) % MOD;
        for (int i = head[h]; i; i = nxt[i]) {
            if (key[i] == k) return val[i];
        }
        return -1;
    }

    // Kiểm tra tồn tại
    bool count(long long k) {
        int h = (k % MOD + MOD) % MOD;
        for (int i = head[h]; i; i = nxt[i]) {
            if (key[i] == k) return true;
        }
        return false;
    }
};