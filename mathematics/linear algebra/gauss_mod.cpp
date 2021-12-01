int gauss() {
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++)
            while (a[j][i]) {
                int t = a[i][i]/a[j][i];
                for (int k = i; k <= n; k++) (a[i][k] -= a[j][k]*t%yzh) %= yzh;
                swap(a[i], a[j]); ans *= -1;
            }
        (ans *= a[i][i]) %= yzh;
    }
    return (ans+yzh)%yzh;
}
