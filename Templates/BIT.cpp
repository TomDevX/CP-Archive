struct BIT{
    ll bit[N];
    int n;

    BIT(int _n = 0) : n(_n) {
        memset(bit,0,sizeof(bit));
    };

    void build(const vi& a){
        for(int i = 1; i <= n; i++){
            bit[i] += a[i];

            int j = i + (i&-i);
            if(j <= n) bit[j] += bit[i];
        }
    }

    void update(int pos, int val){
        for(; pos <= n; pos += pos&-pos){
            bit[pos] += val;
        }
    }

    ll prefSum(int pos){
        ll ans = 0;
        for(; pos; pos -= pos&-pos){
            ans += bit[pos];
        }
        return ans;
    }

    ll query(int l, int r){
        return prefSum(r) - prefSum(l-1);
    }
};