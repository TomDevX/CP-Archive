#include <iostream>
#include <vector>

using namespace std;

bool isPalindrome(string s){
    for (int i = 0; i < s.size() / 2; i++){
        if(s[i] != s[s.size() - i - 1]){
            return false;
        }
    }
    return true;
}

void solve(string s){
    string temps = s;
    s.insert(0, "a");
    if(!isPalindrome(s)){
        cout << "YES" << endl;
        cout << s << endl;
        return;
    }
    s = temps;
    s.insert(s.size()-1, "a");
    if(!isPalindrome(s)){
        cout << "YES" << endl;
        cout << s << endl;
        return;
    }
    cout << "NO" << endl;
}

int main(){
    int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        string str;
        cin >> str;
        solve(str);
    }
}