template<typename T>
struct BSGS {
    T cal(T a, T b, T c) {
        mp.clear();
        T tim = ceil(sqrt(c)), tmp = b%c;
        for (int i = 0; i <= tim; i++) {
            mp[tmp] = i; tmp = (__int128)tmp*a%c;
        }
        T t = tmp = quick_pow(a, tim, c);
        for (int i = 1; i <= tim; i++) {
            if (mp.count(tmp)) return tim*i-mp[tmp];
            tmp = (__int128)tmp*t%c;
        }
        return -1;
    }
} ;
