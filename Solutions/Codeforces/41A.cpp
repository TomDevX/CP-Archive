#include <iostream>

using namespace std;

string Palindromer(string str){
    string palindromed = str;
    for (int i = str.size()-1; i >= 0; i--)
    {
        palindromed[i] = str[str.size() - i - 1];
    }
    return palindromed;
}

int main(){
    string str;
    string t;
    cin >> str;
    cin >> t;

    string new_str = Palindromer(str);
    if (t == new_str)
    {
        cout << "YES";
    }
    else{
        cout << "NO";
    }
}