#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    while(n--){
        string s;
        cin >> s;
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        if(s == "YES"){
            cout << "YES" << "\n";
            continue;
        }
        cout << "NO" << "\n";
    }
}