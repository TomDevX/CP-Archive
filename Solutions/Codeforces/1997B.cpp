#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                ++rank[rootX];
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int toIndex(int row, int col, int n) {
    return row * n + col;
}

bool inBounds(int row, int col, int n) {
    return row >= 0 && row < 2 && col >= 0 && col < n;
}

int countRegions(const vector<string> &grid, int n) {
    UnionFind uf(2 * n);
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '.') {
                for (const auto& dir : directions) {
                    int ni = i + dir.first;
                    int nj = j + dir.second;
                    if (inBounds(ni, nj, n) && grid[ni][nj] == '.') {
                        uf.unite(toIndex(i, j, n), toIndex(ni, nj, n));
                    }
                }
            }
        }
    }

    set<int> uniqueParents;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '.') {
                uniqueParents.insert(uf.find(toIndex(i, j, n)));
            }
        }
    }

    return uniqueParents.size();
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<string> grid(2);
        for (int i = 0; i < 2; ++i) {
            cin >> grid[i];
        }

        int initialRegions = countRegions(grid, n);
        int criticalCells = 0;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '.') {
                    grid[i][j] = 'x';
                    int newRegions = countRegions(grid, n);
                    if (newRegions == 3) {
                        criticalCells++;
                    }
                    grid[i][j] = '.';
                }
            }
        }

        cout << criticalCells << endl;
    }
}