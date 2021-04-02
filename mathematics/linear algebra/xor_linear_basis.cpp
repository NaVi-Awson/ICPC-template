template<const int N>
struct base {
    long long a[N+5], st[N+5];// st[i] : i << 1
    base () {
        memset(a, 0, sizeof(a));
        st[0] = 1;
        for (int i = 1; i <= N; i++) st[i] = (st[i-1]<<1);
    }
    void insert(long long x) {
        for (int i = N; i >= 0; i--)
            if (x&st[i]) {
                if (!a[i]) {
                    a[i] = x;
                    break;
                }
                else x ^= a[i];
            }
    }
    bool find(long long x) {
        for (int i = N; i >= 0; i--)
            if (x&st[i]) x ^= a[i];
        return !x;
    }
    int size() {
        int cnt = 0;
        for (int i = N; i >= 0; i--)
            if (a[i]) ++cnt;
        return cnt;
    }
    long long getmax() {
        long long maxn = 0;
        for (int i = N; i >= 0; i--)
            maxn = max(maxn, (maxn^a[i]));
        return maxn;
    }
    void clear() {
        for (int i = N; i >= 0; i--)
            a[i] = 0;
    }
    void merge(base b) {
        for (int i = N; i >= 0; i--) {
            insert(b.a[i]);
        }
    }
} ;
