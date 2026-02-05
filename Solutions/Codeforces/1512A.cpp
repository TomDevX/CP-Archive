#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int x;
        cin >> x;
        vector<int> a(x);
        for (int i = 0; i < x; i++)
        {
            cin >> a[i];
        }
        vector<int> temp_a = a;
        sort(a.begin(), a.end());
        if (a[0] == a[1])
        {
            auto it = find(temp_a.begin(), temp_a.end(), a[x - 1]);
            cout << (it + 1) - temp_a.begin() << endl;
        }
        else
        {
            auto it = find(temp_a.begin(), temp_a.end(), a[0]);
            cout << (it + 1) - temp_a.begin() << endl;
        }   
    }
}