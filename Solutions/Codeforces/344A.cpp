#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int count = 0;
    int x;
    cin >> x;
    int current = x;
    n--;

    while(n--){
        int x;
        cin >> x;
        if(x != current){
            count++;
            current = x;
        }
    }
    cout << count+1;
}