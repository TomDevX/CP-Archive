#include <iostream>
#include <algorithm> // sort and math

using namespace std;

int main(){
    int n;
    cin >> n;
    int capacity = 0;
    int x = 0;

    while(n--){
        int enter = 0, exit = 0;
        cin >> exit >> enter;
        x -= exit;
        x += enter;
        capacity = max(capacity, x);
    }
    cout << capacity;
}