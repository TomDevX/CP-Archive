#include <iostream>

using namespace std;

int main(){
    int x;
    cin >> x;
    for (int i = 0; i < x; i++){
        int n;
        cin >> n;
        if(n == 1){
            cout << "HARD";
            return 0;
        }
    }
    cout << "eAsY";
}