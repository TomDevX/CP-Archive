#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void fast() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

// Function to calculate frequency of characters from 'a' to 'z'
vector<vector<int>> prefix_frequency(const string& s, int n) {
    vector<vector<int>> frequency(26, vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            frequency[j][i + 1] = frequency[j][i];
        }
        frequency[s[i] - 'a'][i + 1]++;
    }
    return frequency;
}

vector<int> frequency(const vector<vector<int>>& frequency, int l, int r) {
    vector<int> substringfreq(26, 0);
    for (int i = 0; i < 26; ++i) {
        substringfreq[i] = frequency[i][r] - frequency[i][l - 1];
    }
    return substringfreq;
}

int main() {
    fast();
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        string s1, s2;
        cin >> s1 >> s2;

        vector<vector<int>> freq1 = prefix_frequency(s1, n);
        vector<vector<int>> freq2 = prefix_frequency(s2, n);

        while (q--) {
            int l, r;
            cin >> l >> r;

            vector<int> freqSub1 = frequency(freq1, l, r);
            vector<int> freqSub2 = frequency(freq2, l, r);

            int count = 0;
            for (int i = 0; i < 26; ++i) {
                count += abs(freqSub1[i] - freqSub2[i]);
            }
            cout << count / 2 << endl;
        }
    }
    return 0;
}