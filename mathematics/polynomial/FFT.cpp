void FFT(dob *A, int o) {
    for (int i = 0; i < n; i++) if (i < R[i]) swap(A[i], A[R[i]]);
    for (int i = 1; i < n; i <<= 1) {
//枚举区间长度
        dob wn(cos(pi/i), sin(pi*o/i)), x, y;
        for(int j = 0; j < n; j += (i<<1)) {
//枚举区间左端点
            dob w(1, 0);
            for(int k = 0; k < i; k++, w *= wn) {
//枚举 k 
                x = A[j+k]; y = w*A[j+i+k];
                A[j+k] = x+y;
                A[j+k+i] = x-y;
            }
        }
    }
}
