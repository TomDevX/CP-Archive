#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int turn = 1;
    for (int i = 1; i <= n; i++){
        if(i == n && i % 2 == 0){
            cout << "I love it ";
            break;
        }
        else if(i == n){
            cout << "I hate it ";
            break;
        }
        if(i % 2 == 0){
            cout << "I love that ";
        }
        else{
            cout << "I hate that ";
        }
    }
}