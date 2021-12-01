void gauss() {
    for (int i = 1; i <= n; i++) {
        int maxline = i;
        for (int j = i+1; j <= n; j++)
            if (fabs(a[maxline][i]) < fabs(a[j][i])) maxline = j;
        if (maxline != i) swap(a[i], a[maxline]);
        if (a[i][i] == 0) {puts("No Solution"); return; }
        for (int j = i+1; j <= n; j++) {
            double div = a[j][i]/a[i][i];
            for (int k = i; k <= n+1; k++)
                a[j][k] -= a[i][k]*div;
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i+1; j <= n; j++)
            a[i][n+1] -= a[i][j]*a[j][n+1];
        a[i][n+1] /= a[i][i];
    }
    for (int i = 1; i <= n; i++) printf("%.2lf\n", a[i][n+1]);
} 
