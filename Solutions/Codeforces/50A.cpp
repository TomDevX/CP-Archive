#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <algorithm> // sort and math
#include <iomanip> // set int
#include <cstdlib> // srand()/rand()
#include <ctime> // time()
#include <unistd.h> // sleep()/usleep()
#include <sstream> // split string
#include <fstream> // files
#include <utility> // pair

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m,n; cin >> m >> n;
    if(m*n % 2 == 0){
        cout << (m * n) / 2;
    }
    else{
        cout << ((m * n) - 1) / 2;
    }
}