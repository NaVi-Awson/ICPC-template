// query maximal a*cnt[a] in [l, r]
int curr = 0, curl = 1, l, r; ll now = 0;
for (int i = 1; i <= m; i++) {
    l = q[i].l, r = q[i].r;
    if (l/block == r/block) {
        ans[q[i].id] = bf(l, r);
        continue;
    }
    if (l/block >= curl/block) {
        for (int i = curl; i <= curr; i++) --cnt[a[i]];
        now = 0;
        curl = (l/block+1)*block;
        curr = curl-1;
    }
    while (curr < r) ++curr, ++cnt[a[curr]], now = max(now, 1ll*cnt[a[curr]]*b[a[curr]]);
    ll pre = now;
    while (curl > l) --curl, ++cnt[a[curl]], now = max(now, 1ll*cnt[a[curl]]*b[a[curl]]);
    ans[q[i].id] = now;
    for (int i = (l/block+1)*block-1; i >= curl; i--)
        --cnt[a[i]];
    now = pre;
    curl = (l/block+1)*block;
}
