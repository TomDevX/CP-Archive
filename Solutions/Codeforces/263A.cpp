#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main(){
    vector<vector<int>> matrix;
    int x;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cin >> x;
            if(x == 1){
                cout << (abs(i - 2) + abs(j - 2));
            }
        }
    }


}