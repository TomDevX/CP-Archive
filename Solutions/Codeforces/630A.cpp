#include <iostream>

using namespace std;

long long int luythua(int b){
    long long int a = 5;
    long long int res = 1;
    while (b > 0)
    {
        if(b % 2 != 0){
            res *= a;
        }
        a *= a;
        b /= 2;
    }
    return res;
}

int main(){
    int b;
    cin >> b;
    string s = to_string(luythua(b));
    cout << s[s.size()-2] << s[s.size()-1];
}