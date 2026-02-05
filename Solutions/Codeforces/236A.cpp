#include <iostream>
#include <vector>

using namespace std;

int main(){
    string name;
    cin >> name;
    int count = 0;
    vector<char> words(26,false);

    for (int i = 0; name[i] != '\0'; ++i){
        int index = name[i] - 'a';
        if(!words[index]){
            words[index] = true;
            count++;
        }
    }

    if (count % 2 == 0){
        cout << "CHAT WITH HER!" << endl;
    }
    else{
        cout << "IGNORE HIM!" << endl;
    }
}