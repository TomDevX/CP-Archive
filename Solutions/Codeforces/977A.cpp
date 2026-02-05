#include <iostream>

using namespace std;

int main(){
    int n, x;
    cin >> n >> x;

    while(x--){
        if(n%10 != 0){
            n--;
            continue;
        }
        else{
            n /= 10;
        }
    }
    cout << n;
}