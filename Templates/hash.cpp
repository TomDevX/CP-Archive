const int N = 1e6+5;
const int MOD1 = 1234567891;
const int MOD2 = 1e9+4567;
const int NUMBER_OF_STRINGS = 2;
int base = 31;

struct HashKey{
    int h1,h2;
    const bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
};

HashKey POW[N];

void init_pow(){
    POW[0] = {1,1};
    for(int i = 1; i < N; i++){
        POW[i].h1 =  (POW[i-1].h1*base)%MOD1;
        POW[i].h2 =  (POW[i-1].h2*base)%MOD2;
    }
}

HashKey Hash[NUMBER_OF_STRINGS*N];
int pool = 0;

void reset_pool(){
    pool = 0;
}

struct PolyHash{
    HashKey *h = nullptr;
    int len = 0;

    PolyHash(){};

    PolyHash(const string &s){
        len = sz(s)-1;
        h = &Hash[pool];
        pool += (len+1);

        for(int i = 1; i <= len; i++){
            h[i].h1 = (h[i].h1*base + s[i] - 'a' + 1)%MOD1;
            h[i].h2 = (h[i].h2*base + s[i] - 'a' + 1)%MOD2;
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
};