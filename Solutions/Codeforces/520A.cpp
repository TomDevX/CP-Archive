#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<bool> check_alphabet(26, false);
    int n;
    cin >> n;
    while(n--){
        char c;
        cin >> c;
        if('A' <= c && c <= 'Z'){
            check_alphabet[c - 'A'] = true;
            continue;
        }
        if('a' <= c && c <= 'z'){
            check_alphabet[c - 'a'] = true;
        }
    }
    for (bool check : check_alphabet) {
        if(check == false){
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}
                    