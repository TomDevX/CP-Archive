#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

struct custom_hash{
    int operator()(const int& x) const{
        return (x^RAND);
    }
};

gp_hash_table<int, int, custom_hash> mp[N];