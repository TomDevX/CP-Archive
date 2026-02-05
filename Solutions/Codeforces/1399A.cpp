#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
void solve(vector<int> num){
    sort(num.begin(), num.end());
    for (int i = 0; i < num.size()-1; i++){
        if(abs(num[i] - num[i+1]) > 1){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
}
 
int main(){
    int t;
    cin >> t;
 
    while(t--){
        int x;
        cin >> x;
        vector<int> num(x);
        for (int i = 0; i < num.size(); i++){
            cin >> num[i];
        }
        solve(num);
    }
}