#include <iostream>

using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < 3; i++){
            sum2 += n % 10;
            n /= 10;
        }
        for (int i = 0; i < 3; i++){
            sum1 += n % 10;
            n /= 10;
        }
        cout << (sum2 == sum1 ? "YES" : "NO") << endl;
    }
}