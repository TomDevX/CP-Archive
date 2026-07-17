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

const unsigned int SPLIT = (1ULL << 32) / (1.0L*((1 + sqrt(5))/2));
struct custom_hash{
    int operator()(const vpii& a) const{
        unsigned int seed = RAND;
        for(const pii& p : a){
            seed ^= p.fi + RAND + SPLIT + (seed << 6) + (seed >> 2);
            seed ^= p.se + RAND + SPLIT + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};