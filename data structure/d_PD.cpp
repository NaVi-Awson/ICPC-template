namespace DPD {
    int size[N+5], mx[N+5], minsize, root, vis[N+5];
    void get_root(int o, int pa, int fa) {
        mx[o] = Max(mx[o], size[pa]-size[o]);
        if (mx[o] < minsize) minsize = mx[o], root = o;
        for (int i = path[o]; i; i = edge[i].next)
            if (edge[i].to != fa && !vis[edge[i].to]) get_root(edge[i].to, pa, o);
    }
    void get_size(int o, int fa) {
        size[o] = 1, mx[o] = 0;
        for (int i = path[o]; i; i = edge[i].next)
            if (edge[i].to != fa && !vis[edge[i].to]) {
                get_size(edge[i].to, o);
                size[o] += size[edge[i].to];
                if (size[edge[i].to] > mx[o]) mx[o] = size[edge[i].to];
            }
    }
    void get_insert(int o, int pa, int da, int fa, int cost) {
        T1.insert(T1.root[da], cost, val[o]); if (pa) T2.insert(T2.root[da], LCA::dist(pa, o), val[o]);
        for (int i = path[o]; i; i = edge[i].next) if (edge[i].to != fa && !vis[edge[i].to]) get_insert(edge[i].to, pa, da, o, cost+edge[i].cost);
    }
    void work(int o, int pa) {
        minsize = INF; get_size(o, 0), get_root(o, o, 0); vis[root] = 1, fa[root] = pa; int rt = root;
        T1.insert(T1.root[root], 0, val[root]); if (pa) T2.insert(T2.root[root], LCA::dist(pa, root), val[root]);
        for (int i = path[root]; i; i = edge[i].next)
            if (!vis[edge[i].to]) get_insert(edge[i].to, pa, root, 0, edge[i].cost);
        for (int i = path[root]; i; i = edge[i].next)
            if (!vis[edge[i].to]) work(edge[i].to, rt);
    }
    void main() {work(1, 0); }
}
