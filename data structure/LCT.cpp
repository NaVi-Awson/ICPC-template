struct LCT {
    int key[N], ch[N][2], val[N], pre[N], isrt[N], rev[N];
    LCT () {memset(isrt, 1, sizeof(isrt)); }
    void pushup(int o) {key[o] = key[ch[o][0]]^key[ch[o][1]]^val[o]; }
    void pushdown(int o) {
        if (!rev[o]) return;
        int ls = ch[o][0], rs = ch[o][1];
        swap(ch[ls][0], ch[ls][1]), swap(ch[rs][0], ch[rs][1]);
        rev[ls] ^= 1, rev[rs] ^= 1; rev[o] = 0;
    }
    void push(int o) {
        if (!isrt[o]) push(pre[o]);
        pushdown(o);
    }
    void rotate(int o, int kind) {
        int p = pre[o];
        ch[p][!kind] = ch[o][kind], pre[ch[o][kind]] = p;
        if (isrt[p]) isrt[o] = 1, isrt[p] = 0;
        else ch[pre[p]][ch[pre[p]][1] == p] = o;
        pre[o] = pre[p];
        ch[o][kind] = p, pre[p] = o;
        pushup(p), pushup(o);
    }
    void splay(int o) {
        push(o);
        while (!isrt[o]) {
            if (isrt[pre[o]]) rotate(o, ch[pre[o]][0] == o);
            else {
                int p = pre[o], kind = ch[pre[p]][0] == p;
                if (ch[p][kind] == o) rotate(o, !kind), rotate(o, kind);
                else rotate(p, kind), rotate(o, kind);
            }
        }
    }
    void access(int o) {
        int y = 0;
        while (o) {
            splay(o);
            isrt[ch[o][1]] = 1;
            isrt[ch[o][1] = y] = 0;
            pushup(o);
            o = pre[y = o];
        }
    }
    void makeroot(int o) {access(o); splay(o); rev[o] ^= 1, swap(ch[o][0], ch[o][1]); }
    void split(int a, int b) {makeroot(a); access(b); splay(b); }
    int find(int o) {access(o); splay(o); while (ch[o][0]) o = ch[o][0]; return o; }
    void link(int a, int b) {if (find(a) == find(b)) return; makeroot(a); pre[a] = b; }
    void cut(int a, int b) {split(a, b); if (ch[b][0] != a) return; isrt[a] = 1; pre[a] = ch[b][0] = 0; pushup(b); }
    int query(int a, int b) {split(a, b); return key[b]; }
    void update(int a, int b) {makeroot(a); val[a] = b; pushup(a); } 
} T;
