#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main(){
    vector<int> numbers;

    for (int x; cin >> x;)
    {
        if(x != '+'){
            numbers.push_back(x);
        }
    }
    sort(numbers.begin(), numbers.end());

    for (int i = 0; i < numbers.size(); i++){
        if(i > 0){
            cout << "+";
        }
        cout << numbers[i];
    }
}