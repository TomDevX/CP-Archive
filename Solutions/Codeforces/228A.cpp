#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> colors;
    for (int i = 0; i < 4; i++)
    {
        int x;
        cin >> x;
        colors.push_back(x);
    }
    sort(colors.begin(), colors.end());
    int current = colors[0];
    int count = 1;
    for (int i = 0; i < 4; i++)
    {
        if(colors[i] != current){
            count++;
            current = colors[i];
        }
    }
    cout << 4 - count;
}