const long long MOD = 1e9+7;
struct Matrix{
    int n,m;
    vector<vector<long long>> mat;

    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m){
        mat = vector<vector<long long>>(n+1,vector<long long>(m+1));
    }

    Matrix init(){
        Matrix res(n,m);
        for(int i = 1; i <= n; i++){
            res.mat[i][i] = 1;
        }
        return res;
    }

    Matrix operator*(Matrix b){
        Matrix res(n, b.m);
        for(int i = 1; i <= n; i++){
            for(int k = 1; k <= m; k++){
                for(int j = 1; j <= b.m; j++){
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k]*b.mat[k][j])%MOD;
                }
            }
        }
        return res;
    }

    Matrix operator^(long long k){
        Matrix res(n,m);
        res = init();
        if(k <= 0) return res;
        Matrix a = *this;

        while(k){
            if(k&1){
                res = res*a;
            }
            a = a*a;
            k >>= 1;
        }
        return res;
    }
};