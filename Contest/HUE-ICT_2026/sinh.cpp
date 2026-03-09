#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <cstring>
#include <random>
#include <fstream>
#include <filesystem>
#include <string>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

#define name "3"
#define TESTS 100

random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<long long> dis(1,(long long)1e18);

long long ranInt(long long l, long long r){
    long long res = 0;
    for (int i = 0; i < 4; i++){
        res = (res << 15) ^ (dis(gen) & ((1LL << 15) - 1LL));
    }
    return l + res % (r - l + 1);
}

void sinh(int test){
    string INP = name ".INP";
    ofstream inp(INP.c_str());

    int n = ranInt(1,1e4);
    int r = ranInt(1,n);
    int l = ranInt(1,r);

    cerr << "Check: " << n << ' ' << l << ' ' << r;

    inp << n << ' ' << l << ' ' << r << '\n';
    for(int i = 1; i <= n; i++){
        inp << ranInt(1,1e4) << ' ' << ranInt(1,1e4) << '\n';
    }

    inp.close();
}

void gen_ans(int test){
    string INP = name ".INP";
    string ANS = name ".ANS";

    string cmd = "./" name "_trau < " + INP + " > " + ANS;
    system(cmd.c_str());
}

bool check(int test){
    string INP = name ".INP";
    string OUT = name ".OUT";

    string cmd = "./" name " < " + INP + " > " + OUT;
    system(cmd.c_str());

    if(system(("diff " name ".OUT " name ".ANS")) != 0){
        return false;
    }
    return true;
}

int main(){
    for (int test = 1; test <= TESTS; test++){
        sinh(test);
        gen_ans(test);

        if(check(test)){
            cout << "Test #" << test << ": OK!\n";
        }
        else{
            cout << "Test #" << test << ": WA!\n";
            return 0;
        }
    }
}