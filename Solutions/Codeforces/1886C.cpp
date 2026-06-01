/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-29 21:27:09
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Decreasing String
 *    source: https://codeforces.com/problemset/problem/1886/C
 *    submission: https://codeforces.com/problemset/submission/1886/376537342
 *    status: AC
 * ----------------------------------------------------------
 *    tags: String, Stack
 *    complexity: O(n)
 *    note: We notice that our optimized way is to delete the character that is to the far left to be smaller than the old one -> compare s[i] with s[i+1]. But how do we delete it without getting O(n) complexity? -> Use stack to store past available elements. To count efficiently, just pos -= current_string_size
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <stack>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()

// --- [ TYPES & ALIASES ] ---
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using pii = pair<int,int>;
using pill = pair<int,long long>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        string s;
        cin >> s;
        ll pos;
        cin >> pos;

        stack<int> st;
        st.push(0);

        int ssize = sz(s);

        for(int i = 1; i < sz(s) && pos > ssize; i++){
            if(st.empty() || s[i] >= s[st.top()]){
                st.push(i);
            }
            else{
                while(pos > ssize && !st.empty() && s[i] < s[st.top()]){
                    s[st.top()] = '#';
                    st.pop();
                    pos -= ssize;
                    ssize--;
                }
                st.push(i);
            }
        }

        int idx = sz(s) - 1;
        while(pos > ssize){
            while(s[idx] == '#') idx--;
            s[idx--] = '#';
            pos -= ssize;
            ssize--;
        }

        int cnt = 0;
        for(int i = 0; i < sz(s); i++){
            if(s[i] != '#') cnt++;
            if(cnt == pos){
                cout << s[i];
                break;
            }
        }
    }
    
    return NAH_I_WOULD_WIN;
}