// w(l, r) means the number of pairs with the same value
int nl = 1, nr; 
void cdq(int l, int r, int L, int R) {
    int MID = (L+R)>>1, mid, loc = MID, pl = nl, pr = nr;
    if (r < MID) loc = r;
    mid = loc;
    while (nr < MID) ans += cnt[a[++nr]]++;
    while (nl > loc) ans += cnt[a[--nl]]++;
    while (nr > MID) ans -= --cnt[a[nr--]];
    while (nl < loc) ans -= --cnt[a[nl++]];
    g[1][MID] = g[0][loc-1]+ans;
    for (int i = loc-1; i >= l; i--) {
        ans += cnt[a[i]]++;
        if (g[0][i-1]+ans < g[1][MID])
            mid = i, g[1][MID] = g[0][i-1]+ans;
    }
    nl = l;
    if (L < MID) cdq(l, mid, L, MID-1);
    if (MID < R) cdq(mid, r, MID+1, R);
    while (nr < pr) ans += cnt[a[++nr]]++;
    while (nl > pl) ans += cnt[a[--nl]]++;
    while (nr > pr) ans -= --cnt[a[nr--]];
    while (nl < pl) ans -= --cnt[a[nl++]];
}
