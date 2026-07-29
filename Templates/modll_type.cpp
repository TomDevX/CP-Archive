#define ll long long

const ll MOD = 1e9+7;

struct modll{
    ll val = 0;
    
    modll() : val(0) {};
    modll(ll x) : val(norm(x)) {};
    
    ll norm(ll x) const noexcept {
        x %= MOD;
        if(x < 0) x += MOD;
        return x;
    }
    
    modll binpow(ll exp) const noexcept {
        modll res = 1;
        modll x = *this;
        while(exp){
            if(exp & 1) res *= x;
            x *= x;
            exp >>= 1;
        }
        return res;
    }
    
    // set operators
    void operator +=(modll x) noexcept {
        val += x.val;
        if(val >= MOD) val -= MOD;
    }
    void operator -=(modll x) noexcept { 
        val -= x.val;
        if(val < 0) val += MOD;
    }
    void operator *=(modll x) noexcept { val = (1ULL*val*x.val)%MOD; }
    void operator /=(modll x) noexcept { *this *= x.binpow(MOD-2); }
    
    // operators
    modll operator +(modll x) const noexcept { 
        ll res = val + x.val;
        return modll(res >= MOD ? res - MOD : res);
    }
    modll operator -(modll x) const noexcept { 
        ll res = val - x.val;
        return modll(res < 0 ? res + MOD : res);
    }
    modll operator *(modll x) const noexcept { return (1ULL*val * x.val)%MOD; }
    modll operator /(modll x) const noexcept { return *this * x.binpow(MOD-2); }
    
    // input/output
    friend std::ostream& operator <<(std::ostream& os, modll x) noexcept { return os << x.val; }
    friend std::istream& operator >>(std::istream& is, modll &x) noexcept {
        ll inp_val;
        is >> inp_val;
        x = modll(inp_val);
        return is;
    }
};
