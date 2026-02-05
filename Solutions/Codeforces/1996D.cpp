#include <iostream>
#include <algorithm>
using namespace std;

int count_triplets(int n, int x) {
    int count = 0;

    for (int a = 1; a <= x; ++a) {
        int max_b = min(x - a, n / a);
        for (int b = 1; b <= max_b; ++b) {
            int max_c1 = (n - a * b) / (a + b);
            int max_c2 = x - a - b;
            int max_c = min(max_c1, max_c2);
            
            if (max_c >= 1) {

                count += max_c;
            }
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        cout << count_triplets(n, x) << endl;
    }

    return 0;
}