for (int i = 1; i <= n; i++) f[i][1] = w(1, i);
for (int i = 1; i <= m; i++) s[n+1][i] = n;
for (int j = 2; j <= m; j++)
    for (int i = n; i >= 1; i--) {
        f[i][j] = INF;
        for (int k = s[i][j-1]; k <= s[i+1][j]; k++) 
            if (f[k][j-1]+w(k+1, i) < f[i][j])
                f[i][j] = f[k][j-1]+w(k+1, i), s[i][j] = k;
    }
