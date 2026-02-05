#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    int count = 0;
    vector<int> scores(n);

    for (int i = 0; i < n; i++){
        cin >> scores[i];
    }

    for (int i = 0; i < n; i++){
        if(scores[i] >= scores[k-1] && scores[i] > 0){
            count++;
        }
    }

    cout << count;
}