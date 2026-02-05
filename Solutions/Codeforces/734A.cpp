#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int A = 0;
    int D = 0;

    for (int i = 0; i < n; i++){
        char c;
        cin >> c;
        if(c == 'A'){
            A++;
        }
        else{
            D++;
        }
    }
    if(A != D){
        cout << (A > D ? "Anton" : "Danik");
    }
    else{
        cout << "Friendship";
    }
}