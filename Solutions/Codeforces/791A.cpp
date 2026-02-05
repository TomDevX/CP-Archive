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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int limak, bob;
    cin >> limak >> bob;
    int count = 0;

    while(limak <= bob){
        count++;
        limak *= 3;
        bob *= 2;
    }
    cout << count;
}