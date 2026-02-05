#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    while(n--){
        vector<int> arr(3);
        for (int i = 0; i < 3; i++){
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end(), greater<int>());
        if(arr[0] == arr[1] + arr[2]){
            cout << "yEs" << "\n";
            continue;
        }
        cout << "NO" << "\n";
    }
}