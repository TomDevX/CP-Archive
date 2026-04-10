#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <algorithm>
#include <TomDev.h>

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

    int n = ranInt(1,20);
    inp << 0 << ' ' << n << '\n';

    int q = ranInt(1,50);
    while(q--){
        int type = ranInt(1,2);
        if(type == 1){
            inp << type << ' ' << ranInt(0,n-1) << ' ' << ranInt(0,n-1) << ' ' << ranInt(1,100) << '\n';
        }
        else{
            int x = ranInt(0,n-1), y = ranInt(0,n-1), u = ranInt(x,n-1), v = ranInt(y,n-1);
            inp << type << ' ' << x << ' ' << y << ' ' << u << ' ' << v << '\n';
        }
    }
    inp << 3;

    inp.close();
}

bool check(){
    string cmd = "VNOJ/nkmobile < input.inp > output.out";
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