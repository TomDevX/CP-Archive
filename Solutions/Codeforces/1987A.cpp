#include <iostream>

using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        int gb, range;
        cin >> gb >> range;

        gb = (gb * range) - (range - 1);
        cout << gb << endl;
    }
}