#include <iostream>
#include <vector>
using namespace std;




struct Node {
   bool en;
   int c[26];
   Node() {
       en = 0;
       for(int i = 0; i < 26; i++) c[i] = -1; // nếu từ Node hiện tại mình đi theo cạnh i thì chưa link đến đâu cả.
       // Node => cạnh a hỏi c[0] == -1 <=> chưa có nút đó => tạo thêm nút mới
                       //    c[0] != -1 <=> mình đã có rồi => đi xuống
   }
};
vector<Node> trie;


// nút của a ở vị trí 5 => trie[5]


void new_node() {
   trie.push_back(Node());
}


void add_string(const string &s) {
   int pos = 0; // vị trí của nút root trong trie


   // nếu code như này thì nút root sẽ ko bao giờ thay đổi gì hết.
   // nếu muốn thay đổi cả root => cnt[root]++;


   for(int i = 0; i < s.size(); i++) {
       int val = s[i] - 'a';
       if(trie[pos].c[val] == -1) {
           // cạnh này chưa tồn tại => mình phải tạo thêm
           new_node(); // tạo thêm 1 nút mới
           trie[pos].c[val] = (int)trie.size() - 1; // tạo cầu thang
       }
       pos = trie[pos].c[val];
   }
   trie[pos].en = 1;
}




// dfs
int ans = 0;
void dfs(int u, int sum) {
   if(trie[u].en) sum++;
   ans = max(ans, sum);
   for(int i = 0; i < 26; i++) {
       if(trie[u].c[i] != -1) {
           dfs(trie[u].c[i], sum);
       }
   }
}


int n, m;
int main() {
   ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   cin >> n;


   // luôn luôn phải tạo nút gốc đầu tiên
   new_node();
   for(int i = 1; i <= n; i++) {
       string s; cin >> s;
       add_string(s);
   }


   dfs(0, 0);
   cout << ans;
}
