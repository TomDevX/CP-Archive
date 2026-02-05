#include <iostream>

using namespace std;


void fast(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}


int main() {
    fast();
    long long int n;
    cin >> n;
    cout << (n % 2 == 0 ? n / 2 : -(n + 1) / 2);
}