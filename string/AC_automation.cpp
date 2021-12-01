struct AC_auto {
    int ch[M][26], key[M], f[M], pos, head, tail, q[M], cnt[M];
    void clear() {
        memset(ch, pos = 0, sizeof(ch));
        memset(key, 0, sizeof(key));
        memset(f, 0, sizeof(f));
        memset(cnt, 0, sizeof(cnt));
    }
    void insert(char *s, int len, int id) {
        int u = 0;
        for (int i = 1; i <= len; i++) {
            if (ch[u][s[i]-'a'] == 0) ch[u][s[i]-'a'] = ++pos;
            u = ch[u][s[i]-'a'];
        }
        key[u] = id;
    }
    void build() {
        head = 0, tail = -1;
        for (int i = 0; i < 26; i++) if (ch[0][i]) q[++tail] = ch[0][i];
        while (head <= tail) {
            int u = q[head++];
            for (int i = 0; i < 26; i++)
                if (ch[u][i]) f[ch[u][i]] = ch[f[u]][i], q[++tail] = ch[u][i];
                else ch[u][i] = ch[f[u]][i];
        }
    }
    void query(char *S, int len) {
        int u = 0;
        for (int i = 1; i <= len; i++) {
            u = ch[u][S[i]-'a']; ++cnt[u];
        }
        for (int i = tail; i >= 0; i--) cnt[f[q[i]]] += cnt[q[i]];
        int maxn = 0;
        for (int i = 1; i <= pos; i++) if (key[i]) maxn = max(maxn, cnt[i]);
        printf("%d\n", maxn);
        for (int i = 1; i <= pos; i++) if (key[i] && cnt[i] == maxn) printf("%s\n", s[key[i]]+1);
    }
} AC;
