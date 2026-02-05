#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int n;
    cin >> n;
    int sum = 0;
    map<string,int> shapes = {{"Tetrahedron", 4}, {"Cube", 6}, {"Octahedron", 8}, {"Dodecahedron", 12}, {"Icosahedron", 20}};
    while(n--){
        string str;
        cin >> str;
        sum += shapes[str];
    }
    cout << sum;
}