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
#include <filesystem> // Use c++17
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;
namespace fs = filesystem;

const string name = "BAI";
#define TESTS 100

random_device rd;
mt19937 gen(rd());

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

long long ranInt(long long l, long long r) {
    uniform_int_distribution<long long> dis(l, r);
    return dis(gen);
}

void sinh(fs::path &inp_path, int test) {
    ofstream inp(inp_path);

    // code

    inp.close();
}

void gen_ans(const fs::path &inp_path, const fs::path &out_path) {
    string trau_program = name + "_trau.exe";
    string cmd = trau_program + " < " + inp_path.string() + " > " + out_path.string();
    system(cmd.c_str());
}

int main() {
    fast();
    fs::path cha = "DE";
    fs::create_directory(cha);
    fs::path root_path = cha/name;
    fs::create_directory(root_path);

    for (int test = 1; test <= TESTS; test++) {
        string test_dir_name = "TEST";
        if (test < 10) test_dir_name += "0" + to_string(test);
        else test_dir_name += to_string(test);

        fs::path test_path = root_path / test_dir_name;
        fs::create_directory(test_path);

        fs::path inp_path = test_path / (name + ".INP");
        fs::path out_path = test_path / (name + ".OUT");

        sinh(inp_path,test);
        gen_ans(inp_path, out_path);
        cout << "Test " << test << ": Completed!\n";
    }
}