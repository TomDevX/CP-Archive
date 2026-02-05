#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        arr[x-1] = i+1;
    }
    for (int j = 0; j < n; j++)
    {
        cout << arr[j] << " ";
    }
}