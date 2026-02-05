#include <iostream>
#include <vector>

using namespace std;
void fast(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}


int main(){
    fast();

    int year = 0;
    cin >> year;
    while(true){
        year++;
        int a = year / 1000;
        int b = year / 100 % 10;
        int c = year / 10 % 10;
        int d = year % 10;

        if(a != b && b != d && c != d && a != c && a != d && b != c){
            break;
        }
    }
    cout << year;
}