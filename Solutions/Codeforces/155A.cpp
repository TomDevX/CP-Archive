#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    n--;
    int base_max;
    cin >> base_max;
    int base_min = base_max;
    int count = 0;
    while (n--)
    {
        int x;
        cin >> x;
        if(x > base_max){
            count++;
            base_max = x;
        }
        else if(x < base_min){
            count++;
            base_min = x;   
        }
    }
    cout << count;
}