template<typename T>
struct exBSGS {
    T cal(T a, T b, T c) {// compute the min x of a^x = b (mod c)
        if (b == 1) return 0;
        T cnt = 0, d = 1, t;
        while ((t = __gcd(a, c)) != 1) {
            if (b%t) return -1;
            ++cnt, b /= t, c /= t, d = (__int128)d*(a/t)%c;
            if (d == b) return cnt;
        }
        mp.clear();
        T tim = ceil(sqrt(c)), tmp = b%c;
        for (int i = 0; i <= tim; i++) {
            mp[tmp] = i; tmp = (__int128)tmp*a%c;
        }
        t = tmp = quick_pow(a, tim, c); tmp = (__int128)tmp*d%c;
        for (int i = 1; i <= tim; i++) {
            if (mp.count(tmp)) return tim*i-mp[tmp]+cnt;
            tmp = (__int128)tmp*t%c;
        }
        return -1;
    }
} ;
