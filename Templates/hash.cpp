const int N = 1e6+5;
const int MOD1 = 1234567891;
const int MOD2 = 1e9+4567;
const int MAXS = 2;
int base = 31;

struct HashKey{
    int h1,h2;
    const bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
    const bool operator<(const HashKey& o) const{
        return (h1 != o.h1 ? h1 < o.h1 : h2 < o.h2);
    }
};

HashKey POW[N];

void init_pow(){
    POW[0] = {1,1};
    for(int i = 1; i < N; i++){
        POW[i].h1 = (POW[i-1].h1*base)%MOD1;
        POW[i].h2 = (POW[i-1].h2*base)%MOD2;
    }
}

HashKey mem[MAXS*N];
int pool = 0;

void reset_pool(){
    pool = 0;
}

struct Hash{
    HashKey *h = nullptr;
    int len = 0;
    const string& s;

    Hash(const string& _s) : s(_s) {
        len = sz(s) - 1;
        h = &mem[pool];
        pool += len+1;

        for(int i = 1; i <= len; i++){
            h[i].h1 = (h[i-1].h1*base + s[i] - 'a' + 1)%MOD1;
            h[i].h2 = (h[i-1].h2*base + s[i] - 'a' + 1)%MOD2;
        }
    }

    HashKey get(int l, int r){
        int seg = r-l+1;
        int res1 = (h[r].h1 - h[l-1].h1*POW[seg].h1)%MOD1;
        int res2 = (h[r].h2 - h[l-1].h2*POW[seg].h2)%MOD2;
        if(res1 < 0) res1 += MOD1;
        if(res2 < 0) res2 += MOD2;
        return {res1,res2};
    }

    int LCP(int l, int r, int u, int v, Hash& o){ // Longest Common Prefix
        int L = 0, R = r-l, ans = -1;
        while(L <= R){
            int mid = L + ((R-L)>>1);

            if(get(l, l + mid) == o.get(u, u + mid)){
                L = mid+1;
                ans = mid;
            }
            else R = mid-1;
        }
        return ans+1;
    }

    int LCS(int l, int r, int u, int v, Hash& o){ // Longest Common Suffix
        int L = 0, R = r-l, ans = -1;
        while(L <= R){
            int mid = L + ((R-L)>>1);

            if(get(r - mid, r) == o.get(v - mid, v)){
                L = mid+1;
                ans = mid;
            }
            else R = mid-1;
        }
        return ans+1;
    }

    int cmp(int l, int r, int u, int v, Hash &o){
        // 0 = same
        // 1 = <
        // 2 = >
        if(r-l == v-u){
            if(get(l,r) == o.get(u,v)) return 0;
            int idx = LCP(l,r,u,v,o);
            return (s[l + idx] < o.s[u + idx] ? 1 : 2);
        }
        if(r-l < v-u){
            int idx = LCP(l,r,u, u + (r-l),o);
            return (l + idx == r || s[l + idx] < o.s[u + idx] ? 1 : 2);
        }
    
    
        int idx = LCP(l,l + (v-u),u, v,o);
        return (u + idx == v || s[l + idx] < o.s[u + idx] ? 1 : 2);
    }
};