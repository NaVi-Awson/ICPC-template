int x[N<<1], y[N<<1], c[N], sa[N], rk[N], height[N];
int m = |{character}|;
void get() {
    int *x = ::x, *y = ::y; 
    for (int i = 1; i <= n; i++) c[x[i] = ch[i]]++;
    for (int i = 2; i <= m; i++) c[i] += c[i-1];
    for (int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n-k+1; i <= n; i++) y[++num] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i]-k;
        for (int i = 1; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 2; i <= m; i++) c[i] += c[i-1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
        swap(x, y); x[sa[1]] = num = 1;
        for (int i = 2; i <= n; i++)
            x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k]) ? num : ++num;
        if ((m = num) == n) break;
    }
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 0) continue;
        if (k) k--;
        int j = sa[rk[i]-1];
        while (i+k <= n && j+k <= n && ch[i+k] == ch[j+k]) ++k;
        height[rk[i]] = k;
    }
}
