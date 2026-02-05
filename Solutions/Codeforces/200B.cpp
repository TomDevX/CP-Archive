#include <iostream>
#include <iomanip> // set int

using namespace std;

int main(){
    int t;
    cin >> t;
    double total = 100 * t;
    double percents = 0;
    while (t--)
    {
        int n;
        cin >> n;
        percents += n;
    }
    cout << fixed << setprecision(12) << (percents / total)*100;
}