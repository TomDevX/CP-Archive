#include <iostream>
#include <vector>

using namespace std;


int main(){
    string s;
    int count = 0;
    getline(cin, s);
    vector<bool> alpha(26, false);
    for (int i = 0; i < s.size() - 1; i++)
    {
        if('a' <= s[i] && s[i] <= 'z'){
            if(alpha[s[i] - 'a'] == false){
                count++;
                alpha[s[i] - 'a'] = true;
            }
        }
    }
    cout << count;
}