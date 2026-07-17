vector<int> pf(string s){
    int n = s.size();
    vector<int> pi(n);
    int j = 0;
    for(int i = 1; i < n; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;  
}

int main(){
    string a,b;
    cin >> a >> b;

    int n = a.size(), m = b.size();
    string t = b+"#" + a;

    vector<int> pi = pf(t);
}