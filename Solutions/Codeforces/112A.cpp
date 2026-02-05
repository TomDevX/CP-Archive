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
#include <sstream> // split string
#include <fstream> // files
#include <utility> // pair

using namespace std;

string toLowerCase(string str){
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    string lowerStr1 = toLowerCase(s1);
    string lowerStr2 = toLowerCase(s2);
    if(lowerStr1 == lowerStr2){
        cout << 0;
    }
    else if(lowerStr1 > lowerStr2){
        cout << 1;
    }
    else{
        cout << -1;
    }
}