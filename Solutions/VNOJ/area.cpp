/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-22 17:57:20
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Diện tích hình chữ nhật
 *    source: https://oj.vnoi.info/problem/area
 *    submission: https://oj.vnoi.info/submission/12168828
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sweep Line 2D, Segment Tree
 *    complexity: O(n \log n)
 *    note: Ở đây, ta mark điểm x bắt đầu của hình chữ nhật tại điểm đó là +1, điểm kết thúc là -1 (do trong bài này ta tính diện tích nên phải lấy điểm kết thúc là end chứ ko phải end + 1), làm thành diff array. Mỗi lần gặp hcn, ta cộng đoạn y lên. Ở đây, BIT sẽ giúp ta làm điều này. Cấu trúc BIT này khá đặc biệt vì 1 node chỉ đại diện cho đoạn của chính nó chứ thằng con cũng không liên quan gì, nên ta ko cần lazy update. Vì khi update xuống, ta luôn +1 trước khi -1 nên đoạn được update sẽ cố định mà không sai sót lấy thẳng con chưa được update. Khi update mà ko có hình chữ nhật nào phủ node hiện tại thì ta lấy kết quả của thằng con (lúc này có lẽ bạn sẽ thắc mắc tại sao node con chưa update mà lấy được, giả sử lúc trước ta đã lazy + xuống, thì giờ node cha mất rồi thì node con cũng sẽ mất, nên lazy chả có tác dụng gì).
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("area.INP", "r")) return;
    freopen("area.INP", "r", stdin);
    freopen("area.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int M = 3e4+2;

struct node{
    int cnt,len;

    node(int _cnt = 0, int _len = 0) : cnt(_cnt), len(_len) {};
};

struct Event{
    int y1,y2,type; // y1 < y2

    Event(int _y1 = 0, int _y2 = 0, int _type = 0) : y1(_y1), y2(_y2), type(_type) {};
};

node st[4*M];
vector<Event> events[M];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int u, int v, int val){
    if(l > v || r < u) return;
    if(l == r){
        st[id].cnt += val;
        if(st[id].cnt > 0) st[id].len = 1;
        else st[id].len = 0;
        return;
    }
    int lc = id<<1;
    if(l >= u && r <= v){
        st[id].cnt += val;
        if(st[id].cnt > 0){
            st[id].len = r-l+1;
        }
        else st[id].len = st[lc].len + st[lc|1].len;
        return;
    }

    int mid = l + ((r-l)>>1);

    update(lc,l,mid,u,v,val);
    update(lc|1,mid+1,r,u,v,val);

    if(st[id].cnt > 0) st[id].len = r-l+1;
    else st[id].len = st[lc].len + st[lc|1].len;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i =1 ; i <= n; i++){
        int x,y,a,b;
        cin >> x >> y >> a >> b;
        events[x].eb(y,b,1);
        events[a].eb(y,b,-1);
    }

    ll ans = 0;
    for(int i = 0; i < M; i++){
        for(const Event &E : events[i]){
            update(1,0,M,E.y1,E.y2-1,E.type);
        }
        ans += 1LL*st[1].len;
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}