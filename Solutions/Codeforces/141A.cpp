#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    string s1;
    string s2;
    string last;
    cin >> s1 >> s2 >> last;
    string s3 = s1 + s2;
    sort(s3.begin(), s3.end());
    sort(last.begin(), last.end());
    if(s3 == last){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
}