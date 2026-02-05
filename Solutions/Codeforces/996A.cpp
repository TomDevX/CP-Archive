#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> bills = {100, 20, 10, 5, 1};
    int bill_index = 0;
    int count = 0;
    while (n > 0)
    {
        if(n >= bills[bill_index]){ // n = 25 >= 100
            count++; // count = 1
            n -= bills[bill_index]; // n - 100 = 25
        }
        else{
            bill_index++;
        }
    }
    cout << count;
}