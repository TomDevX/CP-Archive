#include <iostream>

using namespace std;

/*int main(){
    int problems, minutes;
    cin >> problems >> minutes;
    int count = 0;

    minutes = 240 - minutes; //104
    int difficulty_time = 5;
    int time_sum = 0;
    while (time_sum+difficulty_time <= minutes && count < problems)
    {
        time_sum += difficulty_time; // 105
        count++; // 6
        difficulty_time += 5; // 35
    }
    std::cout << count;
}*/

int main(){
    int problems, minutes;
    cin >> problems >> minutes;
    minutes = 240 - minutes;
    int sum = 0;
    int count = 0;
    for (int i = 1; i <= problems; i++)
    {
        sum += 5 * i;
        if(sum > minutes){
            break;
        }
        count++;
    }
    cout << count;
}