#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

/*int main(){
    int t;
    cin >> t;
    while(t--){
        double a, b;
        cin >> a >> b;
        if(max(a,b) - min(a,b) > 10){
            cout << fixed << setprecision(0) << abs(ceil((max(a,b) - min(a,b)) / 10))<< "\n";
        }
        else if((max(a,b) - min(a,b)) <= 10 && (max(a,b) - min(a,b)) > 0){
            cout << 1 << "\n";
        }
        else{
            cout << 0 << "\n";
        }
    }
}*/

int main(){
    int t;
    cin >> t;
    while(t--){
        int a, b;
		cin >> a >> b;
		cout << (abs(a - b) + 9) / 10 << endl;
    }
}