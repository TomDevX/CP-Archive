#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int time(const string &s) {
    int time = 2;
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == s[i-1]) {
            time += 1;
        } else {
            time += 2;
        }
    }
    return time;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        string s;
        cin >> s;
        
        int max_time = 0;
        string best;
        
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            for (int i = 0; i <= s.length(); ++i) {
                string newpass = s.substr(0, i) + ch + s.substr(i);
                int new_time = time(newpass);
                
                if (new_time > max_time) {
                    max_time = new_time;
                    best = newpass;
                }
            }
        }
        
        cout << best << endl;
    }
}