void FWT(int *A, int o) { // or and xor
    for (int i = 1; i < (1<<n); i <<= 1)
        for (int j = 0; j < (1<<n); j += (i<<1))
            for (int k = 0, x, y; k < i; k++) {
                x = A[j+k], y = A[j+k+i];
                if (o == 0) A[j+k] = x, A[j+k+i] = (x+y)%yzh;
                else if (o == 1) A[j+k] = (x+y)%yzh, A[j+k+i] = y;
                else A[j+k] = (x+y)%yzh, A[j+k+i] = (x-y)%yzh;
            }
}
void iFWT(int *A, int o) {
    for (int i = 1; i < (1<<n); i <<= 1)
        for (int j = 0; j < (1<<n); j += (i<<1))
            for (int k = 0, x, y; k < i; k++) {
                x = A[j+k], y = A[j+k+i];
                if (o == 0) A[j+k] = x, A[j+k+i] = (y-x)%yzh;
                else if (o == 1) A[j+k] = (x-y)%yzh, A[j+k+i] = y;
                else A[j+k] = 1ll*(x+y)*inv%yzh, A[j+k+i] = 1ll*(x-y)*inv%yzh;
            }
}
