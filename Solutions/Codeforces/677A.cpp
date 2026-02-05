#include <iostream>

using namespace std;

int main(){
    int n, h;
    cin >> n >> h;
    int count = 0;

    while(n--){
        int a;
        cin >> a;

        if(a > h){
            count += 2;
        }
        else{
            count++;
        }
    }

    cout << count;
}