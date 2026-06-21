const int N = 1e6+5;

int phi[N];

void sieve(){
    for(int i = 1; i < N; i++) phi[i] = i;

    for(int i = 2; i < N; i++){
        if(phi[i] == i){
            for(int j = i; j < N; j += i){
                phi[j] -= phi[j]/i;
            }
        }
    }
}