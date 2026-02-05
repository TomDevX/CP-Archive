#include <iostream>
#include <algorithm>

using namespace std;

int findmiddle(int a,int b, int c){
    return (a + b + c) - max(max(a, b), c) - min(min(a, b), c);
}

int main(){
    int a, b, c;
    cin >> a >> b >> c;
    int mid = findmiddle(a, b, c);
    cout << (max(max(a, b), c) - mid) + (mid - min(min(a, b), c));
}