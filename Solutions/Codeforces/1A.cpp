#include <iostream>
#include <cmath>
#include <iomanip>  // for setprecision() function

using namespace std;

int main(){
    double a, b, c;
    cin >> a >> b >> c;
    cout << fixed << setprecision(0) << ceil((a/c)) * ceil((b/c));
}