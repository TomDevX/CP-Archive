#include <iostream>

using namespace std;

int main(){
    int x, y;
    cin >> x >> y;
    int current = 2;
    for (int i = 0; i < x; i++)
    {
        if(i % 2 == 1){
            if(current == 2){
                for (int j = 0; j < y - 1; j++){
                    cout << '.';
                }
                cout << '#';
                current = 1;
            }
            else{
                cout << '#';
                current = 2;
                for (int j = 0; j < y - 1; j++){
                    cout << '.';
                }
            }
        }
        else{
            for (int j = 0; j < y; j++){
                cout << '#';
            }
        }
        cout << "\n";
    }
}