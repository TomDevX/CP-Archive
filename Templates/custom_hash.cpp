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

struct custom_hash_vector_pair {
    int operator()(const vector<pair<int, int>>& v) const {
        int seed = 0;
        for (const auto& p : v) {
            seed ^= p.first + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= p.second + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};