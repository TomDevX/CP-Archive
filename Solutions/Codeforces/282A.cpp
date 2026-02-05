#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sstream>
#include <utility>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x;
    cin >> x;
    int target = 0;
    for (int i = 0; i < x; i++)
    {
        string str;
        cin.ignore();
        cin >> str;
        if (str == "++X" || str == "X++")
        {
            target++;
        }
        else{
            target--;
        }
    }
    cout << target;
}