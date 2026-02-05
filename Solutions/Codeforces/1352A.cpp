#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    while(n--){
        int x;
        cin >> x;
        vector<int> num;
        int pow = 1;
        while (x > 0)
        {
            if(x%10 > 0){
                num.push_back((x % 10) * pow);
            }
            x /= 10;
            pow *= 10;
        }
        cout << num.size() << "\n";
        for (int i = num.size() - 1; i >= 0; i--)
        {
            cout << num[i] << " ";
        }
        cout << "\n";
    }
}