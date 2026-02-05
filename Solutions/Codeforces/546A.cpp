#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <algorithm> // sort and math
#include <iomanip> // set int
#include <cstdlib> // srand()/rand()
#include <ctime> // time()
#include <unistd.h> // sleep()/usleep()
#include <cctype> // tolower()/toupper()
#include <sstream> // split string
#include <fstream> // files
#include <utility> // pair

using namespace std;

int moneyhastopay(int k, int w){
    int total = 0;
    for (int i = 1; i <= w; i++)
    {
        total += i * k;
    }
    return total;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int k; // dollars
    int n; // money owned
    int w; // bananas
    cin >> k >> n >> w;
    int holder = moneyhastopay(k, w);
    if (holder > n)
    {
        cout << holder - n;
    }
    else{
        cout << 0;
    }
}