#include <iostream>

using namespace std;

int main(){
    int n, a;
    cin >> n >> a;
    int maxi = 0;
    int mini = 0;
    int max_int = a;
    int min_int = a;
    for (int i = 1; i < n; i++){
        int x;
        cin >> x;
        if(x > max_int){
            max_int = x;
            maxi = i;
        }
        else if(x <= min_int){
            min_int = x;
            mini = i;
        }
    }
    cout << maxi + (n - mini - 1) - (mini < maxi ? 1 : 0);
}