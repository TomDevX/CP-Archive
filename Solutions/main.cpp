#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;

    // 1. Tìm tất cả các ước của n
    vector<int> divs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i * i != n) divs.push_back(n / i);
        }
    }
    
    // 2. Sắp xếp tăng dần
    sort(divs.begin(), divs.end());
    
    // 3. Tham lam phân nhóm
    vector<vector<int>> groups;
    for (int x : divs) {
        bool placed = false;
        for (auto &g : groups) {
            if (x % g.back() == 0) {
                g.push_back(x);
                placed = true;
                break;
            }
        }
        if (!placed) {
            groups.push_back({x});
        }
    }
    
    // 4. In theo đúng format yêu cầu
    cout << groups.size() << '\n';
    for (const auto &g : groups) {
        cout << g.size() << ' ';
        for (size_t i = 0; i < g.size(); i++) {
            cout << g[i] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    // Tối ưu I/O tốc độ cao
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}