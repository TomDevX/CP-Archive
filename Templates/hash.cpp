const int MOD_USE = 5, N = 1e5+5;

const ll MOD[5] = {1234567891, (int)1e9 + 6697, (int)1e9 + 6769, (int)1e9 + 4567, (int)1e9 + 4569};
ll hashA[MOD_USE][N], POW[MOD_USE][N];
int base = 31;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n){
    for(int id = 0; id < MOD_USE; id++){
        POW[id][0] = 1;
        for(int i = 1; i <= n; i++){
            POW[id][i] = (POW[id][i-1]*base)%MOD[id];
        }
    }
}

ll getA(int id, int l, int r){
    return ((hashA[id][r] - hashA[id][l-1]*POW[id][r-l+1])%MOD[id] + MOD[id])%MOD[id];
}