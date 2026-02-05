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

    int n;
    cin >> n;
    string str;
    cin >> str;
    char current = str[0];
    int count = 0;

    for (int i = 1; i < str.size(); i++){
        if(str[i] == current){
            count++;
        }
        else{
            current = str[i];
        }
    }
    cout << count;
}