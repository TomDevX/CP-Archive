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
    string str;
    getline(cin, str);
    int count_upper = 0;
    int count_lower = 0;

    for (int i = 0; i < str.size(); i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            count_upper++;
        }
        else{
            count_lower++;
        }
    }
    if(count_upper > count_lower){
        transform(str.begin(), str.end(), str.begin(), ::toupper);
    }
    else{
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    cout << str;
}