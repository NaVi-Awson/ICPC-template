template<typename T>
struct exLucas {
    T quick_pow(T a, T b, T p) {
        T ans = 1;
        while (b) {
            if (b&1) ans = (__int128)ans*a%p;
            b >>= 1, a = (__int128)a*a%p;
        }
        return ans;
    }
    void ex_gcd(T a, T b, T &x, T &y) {
        if (b == 0) {x = 1, y = 0; return; }
        ex_gcd(b, a%b, x, y);
        T t = x; x = y, y = t-a/b*y;
    }
    T inv(T a, T p) {
        T x, y; ex_gcd(a, p, x, y);
        return (x%p+p)%p;
    }
    T mul(T n, T pi, T pk) {
        if (!n) return 1;
        T ans = 1;
        for (int i = 2; i <= pk; i++) if (i%pi != 0) ans = (__int128)ans*i%pk;
        ans = quick_pow(ans, n/pk, pk);
        for (int i = 2; i <= n%pk; i++) if (i%pi != 0) ans = (__int128)ans*i%pk;
        return (__int128)ans*mul(n/pi, pi, pk)%pk;
    }
    T C(T n, T m, T pi, T pk, T p) {
        T a = mul(n, pi, pk), b = mul(m, pi, pk), c = mul(n-m, pi, pk);
        T k = 0;
        for (T i = n; i; i /= pi) k += i/pi;
        for (T i = m; i; i /= pi) k -= i/pi;
        for (T i = n-m; i; i /= pi) k -= i/pi;
        return (__int128)a*inv(b, pk)%pk*inv(c, pk)%pk*quick_pow(pi, k, pk)%pk;
    }
    T ex_lucas(T n, T m, T p) {// return C(n, m) mod p
        T ans = 0;
        for (T i = 2, x = p; i <= x; i++)
            if (x%i == 0) {
                T k = 1; while (x%i == 0) k *= i, x /= i;
                (ans += (__int128)C(n, m, i, k, p)*(p/k)%p*inv(p/k, k)%p) %= p;
            }
        return ans;
    }
} ;
