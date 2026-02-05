#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int a, b;
    cin >> a >> b;

    int min_int = min(a, b);

    cout << min_int << ' ';
    a -= min_int;
    b -= min_int;
    cout << max(a, b)/2;
}