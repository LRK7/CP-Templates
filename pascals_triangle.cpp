const int MOD = 1e9+7;
int C[1001][1001];

void pascals_triangle() {
    for (int i = 0; i < 1001; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j){
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
}
