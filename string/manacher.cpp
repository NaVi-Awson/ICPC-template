for (int i = 1; i <= len; i++)
    s[++loc] = '$', s[++loc] = ch[i];
s[++loc] = '$', s[++loc] = '#';
int ans = 0, mx = 0, p = 0;
for (int i = 1; i <= loc; i++) {
    if (mx > i) l[i] = min(mx-i, l[(p<<1)-i]);
    else l[i] = 1;
    while (s[i+l[i]] == s[i-l[i]]) ++l[i];
    if (i+l[i] > mx) mx = i+l[i], p = i;
    ans = max(ans, l[i]-1);
}
