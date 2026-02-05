#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int t;
    cin >> t;
    vector<int> a;

    while(t--){
        int x;
        cin >> x;
        a.push_back(x);
    }
    sort(a.begin(), a.end());
    int sum = 0;
    for (int i = 0; i < a.size()-1; i++){
        sum += a[a.size() - 1] - a[i];
    }
    cout << sum;
}