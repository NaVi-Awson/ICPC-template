template<const int N, const int mod, const int g0>
struct cal_NTT {
    int a[N+5], b[N+5], R[N+5], n, m, len, L;
    int quick_pow(int a, int b) {
        int ans = 1;
        while (b) {
            if (b&1) ans = 1ll*a*ans%mod;
            a = 1ll*a*a%mod, b >>= 1;
        }
        return ans;
    }
    void init(int *A, int *B, int lenA, int lenB) {
        n = lenA, m = lenB;
        for (len = 1, L = 0; len <= n+m; len <<= 1) ++L;
        for (int i = 0; i < len; i++) R[i] = (R[i>>1]>>1)|((i&1)<<(L-1));
        for (int i = 0; i <= n; i++) a[i] = A[i];
        for (int i = n+1; i < len; i++) a[i] = 0;
        for (int i = 0; i <= m; i++) b[i] = B[i];
        for (int i = m+1; i < len; i++) b[i] = 0;
    }
    void NTT(int *A, int n, int o) {
        for (int i = 0; i < n; i++) if (i < R[i]) swap(A[i], A[R[i]]);
        for (int i = 1; i < n; i <<= 1) {
            int gn = quick_pow(g0, (mod-1)/(i<<1)), x, y;
            if (o == -1) gn = quick_pow(gn, mod-2);
            for (int j = 0; j < n; j += (i<<1)) {
                int g = 1;
                for (int k = 0; k < i; k++, g = 1ll*g*gn%mod) {
                    x = A[j+k], y = 1ll*g*A[j+k+i]%mod;
                    A[j+k] = (x+y)%mod;
                    A[j+k+i] = (x-y)%mod;
                }
            }
        }
        if (o == 1) return;
        int inv = quick_pow(n, mod-2);
        for (int i = 0; i < n; i++) A[i] = 1ll*A[i]*inv%mod;
    }
    void work() {
        NTT(a, len, 1), NTT(b, len, 1);
        for (int i = 0; i < len; i++) a[i] = 1ll*a[i]*b[i]%mod;
        NTT(a, len, -1);
    }
} ;
