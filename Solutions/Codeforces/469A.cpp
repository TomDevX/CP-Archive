#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

void removeWhitespace(string& input) {
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
}

int main(){
    int n;
    cin >> n;
    vector<bool> check(n+1,false);
    int levels;
    cin >> levels;
    for (int i = 0; i < levels; i++)
    {
        int x;
        cin >> x;
        check[x] = true;
    }

    cin >> levels;
    for (int i = 0; i < levels; i++)
    {
        int x;
        cin >> x;
        check[x] = true;
    }
    for (int i = 1; i <= n; i++){
        if(check[i] == false){
            cout << "Oh, my keyboard!";
            return 0;
        }
    }
    cout << "I become the guy.";
}