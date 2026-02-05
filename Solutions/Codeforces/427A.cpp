#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    int crime = 0;
    int police = 0;
    while (n--)
    {
        int x;
        cin >> x;
        if(x < 0){
            if(police >= abs(x)){
                police-=abs(x);
            }
            else{
                crime+=abs(x);
            }
        }
        else{
            police+= x;
        }
    }
    cout << crime;
}