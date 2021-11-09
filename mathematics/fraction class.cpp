template<typename T> struct fraction {
    T numerator, denominator;
    fraction () {}
    fraction (T _numerator, T _denominator = 1) {
        assert(_denominator);
        T gcd = __gcd(_numerator, _denominator);
        numerator = _numerator/gcd, denominator = _denominator/gcd;
    }
    bool operator == (const fraction &b) const {
        return numerator == b.numerator && denominator == b.denominator;
    }
    bool operator != (const fraction &b) const {
        return numerator != b.numerator || denominator != b.denominator;
    }
    bool operator < (const fraction &b) const {
        return (__int128)numerator*b.denominator < (__int128)b.numerator*denominator;
    }
    bool operator > (const fraction &b) const {
        return (__int128)numerator*b.denominator > (__int128)b.numerator*denominator;
    }
    bool operator <= (const fraction &b) const {
        return (__int128)numerator*b.denominator <= (__int128)b.numerator*denominator;
    }
    bool operator >= (const fraction &b) const {
        return (__int128)numerator*b.denominator >= (__int128)b.numerator*denominator;
    }
    fraction operator + (const fraction &b) const {
        __int128 _numerator = (__int128)numerator*b.denominator+(__int128)b.numerator*denominator;
        __int128 _denominator = (__int128)denominator*b.denominator;
        __int128 gcd = __gcd(_numerator, _denominator);
        return fraction(_numerator/gcd, _denominator/gcd);
    }
    fraction operator - (const fraction &b) const {
        __int128 _numerator = (__int128)numerator*b.denominator-(__int128)b.numerator*denominator;
        __int128 _denominator = (__int128)denominator*b.denominator;
        __int128 gcd = __gcd(_numerator, _denominator);
        return fraction(_numerator/gcd, _denominator/gcd);
    }
    fraction operator * (const fraction &b) const {
        __int128 _numerator = (__int128)numerator*b.numerator;
        __int128 _denominator = (__int128)denominator*b.denominator;
        __int128 gcd = __gcd(_numerator, _denominator);
        return fraction(_numerator/gcd, _denominator/gcd);
    }
    fraction operator / (const fraction &b) const {
        __int128 _numerator = (__int128)numerator*b.denominator;
        __int128 _denominator = (__int128)denominator*b.numerator;
        __int128 gcd = __gcd(_numerator, _denominator);
        return fraction(_numerator/gcd, _denominator/gcd);
    }
} ;
