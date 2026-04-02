struct BIT{
    ll bit[N][2];
    int n;

    BIT(int _n = 0) : n(_n) {
        for(int i = 1; i <= n; i++) bit[i][0] = bit[i][1] = 0;
    };

    void build(vi &a){
        for(int i = 1; i <= n; i++){
            ll diff = a[i] - a[i-1];
            ll d = 1LL*i*diff;

            bit[i][0] += diff;
            bit[i][1] += d;

            int j = i + (i&-i);
            if(j <= n){
                bit[j][0] += bit[i][0];
                bit[j][1] += bit[i][1];
            }
        }
    }

    void update_point(int id, int pos, int val){
        for(;pos <= n; pos += pos&-pos){
            bit[pos][id] += val;
        }
    }

    void update_range(int l, int r, int val){
        update_point(0,l,val);
        update_point(0,r+1,-val);
        update_point(1,l,1LL*l*val);
        update_point(1,r+1,1LL*-(r+1)*val);
    }

    ll get(int pos){
        ll suma = 0, sumb = 0;
        int ori = pos;
        for(; pos; pos -= pos&-pos){
            suma += bit[pos][0];
            sumb += bit[pos][1];
        }
        return 1LL*(ori+1)*suma - sumb;
    }

    ll query(int l, int r){
        return get(r) - get(l-1);
    }
};