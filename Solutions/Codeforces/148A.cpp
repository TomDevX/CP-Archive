#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int a, int b){
    if(a == 0 || b == 0){
        return a+b;
    }
    while(a*b != 0){
        if(a > b){
            a = a % b; // or a = a/b
        }
        else{
            b = b % a; // or b = b/a
        }
    }
    return a + b;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// Hàm tìm LCM của bốn số
template<typename... Args>
int lcm(int a, Args... args) {
    return lcm(a, lcm(args...));
}

int main() {
    int k, l, m, n, d;
    cin >> k >> l >> m >> n >> d;

    int count_k = d / k;
    int count_l = d / l;
    int count_m = d / m;
    int count_n = d / n;

    int count_kl = d / lcm(k, l);
    int count_km = d / lcm(k, m);
    int count_kn = d / lcm(k, n);
    int count_lm = d / lcm(l, m);
    int count_ln = d / lcm(l, n);
    int count_mn = d / lcm(m, n);

    int count_klm = d / lcm(k, l, m);
    int count_kln = d / lcm(k, l, n);
    int count_kmn = d / lcm(k, m, n);
    int count_lmn = d / lcm(l, m, n);
    int count_klmn = d / lcm(k, l, m, n);

    int result = count_k + count_l + count_m + count_n
               - count_kl - count_km - count_kn - count_lm - count_ln - count_mn
               + count_klm + count_kln + count_kmn + count_lmn
               - count_klmn;

    cout << result << endl;

    return 0;
}