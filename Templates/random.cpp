mt19937_64 gen(random_device{}());
uniform_int_distribution<long long> dist;

long long ranInt(long long l, long long r){
    return dist(gen, uniform_int_distribution<long long>::param_type(l,r));
}