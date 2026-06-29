// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;
const ll MOD = 1e9+7;

ll fac[N], inv[N];

// ----------------------- [ FUNCTIONS ] -----------------------
ll binpow(ll a, ll k){
    ll res = 1;
    while(k){
        if(k&1) res = (res*a)%MOD;
        a = (a*a)%MOD;
        k >>= 1;
    }
    return res;
}

void preprocess(){
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = (fac[i-1]*i)%MOD;

    inv[N-1] = binpow(fac[N-1],MOD-2);
    for(int i = N-2; i >= 0; i--) inv[i] = (inv[i+1]*(i+1))%MOD;
}

ll findC(int n, int k){
    if(n < 0 || k < 0 || k > n) return 0;
    return ((fac[n]*inv[n-k]%MOD)*inv[k])%MOD;
}