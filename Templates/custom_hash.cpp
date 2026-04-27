random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<ll> dis(1,1e18);
const ll RAND = dis(gen);

struct custom_hash{
    int operator()(const int& x) const{
        return (x^RAND);
    }
};

struct custom_hash_pair{
    int operator()(const pair<int,int>& x) const{
        return (x.fi*31 + x.se)^RAND;
    }
};