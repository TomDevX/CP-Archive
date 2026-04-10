#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <algorithm>

#if __has_include("TomDev.h")
    #include <TomDev.h>
#else
#endif

using namespace std;

#define ll long long

random_device rd;
mt19937_64 gen(rd());

uniform_int_distribution<ll> dist(1,1e9);

ll ranInt(ll l, ll r){
    ll res = 0;
    for(int i = 0; i < 4; i++){
        res = (res << 15) ^ (dist(gen) & ((1LL << 15) - 1LL));
    }
    return l + res%(r-l+1);
}

void make(){
    ofstream inp("input.inp");

    int n = ranInt(1,100), q = ranInt(1,100);
    inp << n << ' ' << q << '\n';

    for(int i = 1; i <= n; i++) inp << ranInt(1,1000) << ' ';
    inp << '\n';
    while(q--){
        int l = ranInt(1,n), r = ranInt(l,n);
        inp << ranInt(1,2) << ' ' << l << ' ' << r << '\n';
    }

    inp.close();
}

bool check(){
    string cmd = "CSES/\"Range Queries\"/1736 < input.inp > output.out";
    string cmd2 = "./trau < input.inp > output.ans";
    if(system(cmd.c_str())) return true;
    if(system(cmd2.c_str())) return true;

    return system("diff output.out output.ans");
}

int main(){
    for(int test = 1; test <= 10; test++){
        make();
        if(!check()){
            cout << "AC on test " << test << '\n';
        }
        else{
            cout << "WA on test " << test << '\n';
            return 0;
        }
    }
}