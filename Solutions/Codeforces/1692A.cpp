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
        vector<int> arr(4);
        for (int i = 0; i < 4; i++)
        {
            cin >> arr[i];
        }
        int max_int = arr[0];
        sort(arr.begin(), arr.end(), greater<int>());
        int count = 0;
        for (int i = 0; i < 4; i++)
        {
            if (arr[i] > max_int)
            {
                count++;
            }
            else
            {
                cout << count << endl;
                break;
            }
        }
    }
}