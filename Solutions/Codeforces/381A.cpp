#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> arr;
    while (n--)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    int Seraja = 0, Dimeja = 0;
    int current = 1;
    int size = arr.size()-1;
    int first = 0;
    while(first <= size)
    {
        if(arr[first] < arr[size]){
            if(current % 2 == 0){
                Dimeja += arr[size];
            }
            else{
                Seraja += arr[size];
            }
            current++;
            size--;
        }
        else{
            if(current % 2 == 0){
                Dimeja += arr[first];
            }
            else{
                Seraja += arr[first];
            }
            current++;
            first++;
        }
    }
    cout << Seraja << " " << Dimeja;
}