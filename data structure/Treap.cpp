struct Treap {
    int sz[N], lev[N], val[N], ch[N][2], tot, root;
    queue<int> Q;
    void newnode(int &o, int k) {
        if (!Q.empty()) o = Q.front(), Q.pop();
        else o = ++tot;
        ch[o][0] = ch[o][1] = 0;
        sz[o] = 1, lev[o] = rand(), val[o] = k;
    }
    inline void pushup(int o) {
        sz[o] = sz[ch[o][0]]+sz[ch[o][1]]+1;
    }
    void split(int o, int k, int &x, int &y) {
        if (!o) x = y = 0;
        else {
            if (sz[ch[o][0]]+1 <= k) x = o, split(ch[o][1], k-(sz[ch[o][0]]+1), ch[x][1], y);
            else y = o, split(ch[o][0], k, x, ch[y][0]);
            pushup(o);
        }
    }
    void splitv(int o, int k, int &x, int &y) {
        if (!o) x = y = 0;
        else {
            if (val[o] <= k) x = o, splitv(ch[o][1], k, ch[x][1], y);
            else y = o, splitv(ch[o][0], k, x, ch[y][0]);
            pushup(o);
        }
    }
    int merge(int x, int y) {
        if (!x || !y) return x+y;
        if (lev[x] >= lev[y]) {
            ch[x][1] = merge(ch[x][1], y);
            pushup(x); return x;
        } else {
            ch[y][0] = merge(x, ch[y][0]);
            pushup(y); return y;
        }
    }
    void insert(int x) {
        int r1, r2;
        splitv(root, x, r1, r2);
        int o;
        newnode(o, x);
        root = merge(merge(r1, o), r2);
    }
    int qry(int x) {
        int r1, r2;
        split(root, x, r1, r2);
        int o = r1;
        while (ch[o][1]) o = ch[o][1];
        merge(r1, r2);
        return val[o];
    }
    void delet(int x) {
        int r1, r2, r3;
        split(root, x-1, r1, r2);
        split(r2, 1, r2, r3);
        Q.push(r2);
        root = merge(r1, r3);
    }
} T;
