#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> num(4);
    for (int i = 0; i < 4; i++)
    {
        cin >> num[i];
    }
    sort(num.begin(), num.end());
    int a = num[3] - num[2];
    int b = num[3] - num[1];
    int c = num[3] - num[0];
    cout << a << " " << b << " " << c;
}