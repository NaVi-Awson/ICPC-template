for (int i = 2; i <= l2; i++) {
    int j = nxt[i-1];
    while (j && s2[i] != s2[j+1]) j = nxt[j];
    nxt[i] = s2[i] == s2[j+1] ? j+1 : 0;
}
for (int i = 1, j = 0; i <= l1; i++) {
    while (j && s1[i] != s2[j+1]) j = nxt[j];
    if (s1[i] == s2[j+1]) ++j;
    if (j == l2) printf("%d\n", i-l2+1);
}
