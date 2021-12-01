namespace PD {
    int size[N+5], mx[N+5], minsize, root, vis[N+5], cnt[N+5], sum[N+5];
    void get_size(int o, int fa) {
        size[o] = 1, mx[o] = 0;
        for (int i = path[o]; i; i = edge[i].next)
            if (edge[i].to != fa && !vis[edge[i].to]) {
                get_size(edge[i].to, o);
                size[o] += size[edge[i].to];
                mx[o] = Max(mx[o], size[edge[i].to]);
            }
    }
    void get_root(int o, int rt, int fa) {
        mx[o] = Max(mx[o], size[rt]-size[o]);
        if (mx[o] < minsize) minsize = mx[o], root = o;
        for (int i = path[o]; i; i = edge[i].next)
            if (edge[i].to != fa && !vis[edge[i].to]) get_root(edge[i].to, rt, o);
    }
    void get_ans(int o, int fa, int dep, int cost) {
        if (dep >= k) return;
        if (cnt[k-1-dep] && ans1 < cost+sum[k-1-dep]) ans1 = cost+sum[k-1-dep], ans2 = cnt[k-1-dep];
        else if (cnt[k-1-dep] && ans1 == cost+sum[k-1-dep]) ans2 += cnt[k-1-dep];
        for (int i = path[o]; i; i = edge[i].next)
            if (edge[i].to != fa && !vis[edge[i].to]) get_ans(edge[i].to, o, dep+1, cost+edge[i].cost);
    }
    void get_update(int o, int fa, int dep, int cost) {
        if (dep >= k) return;
        if (sum[dep] < cost) sum[dep] = cost, cnt[dep] = 1;
        else if (sum[dep] == cost) ++cnt[dep];
        for (int i = path[o]; i; i = edge[i].next)
            if (edge[i].to != fa && !vis[edge[i].to]) get_update(edge[i].to, o, dep+1, cost+edge[i].cost);
    }
    void get_clean(int o, int fa, int dep) {
        if (dep >= k) return;
        cnt[dep] = 0, sum[dep] = 0;
        for (int i = path[o]; i; i = edge[i].next)
            if (edge[i].to != fa && !vis[edge[i].to]) get_clean(edge[i].to, o, dep+1);
    }
    void work(int o) {
        minsize = INF;
        get_size(o, 0), get_root(o, o, 0);
        vis[root] = 1; cnt[0] = 1;
        for (int i = path[root]; i; i = edge[i].next)
            if (!vis[edge[i].to]) get_ans(edge[i].to, root, 1, edge[i].cost), get_update(edge[i].to, root, 1, edge[i].cost);
        cnt[0] = 0;
        for (int i = path[root]; i; i = edge[i].next)
            if (!vis[edge[i].to]) get_clean(edge[i].to, root, 1);
        for (int i = path[root]; i; i = edge[i].next)
            if (!vis[edge[i].to]) work(edge[i].to);
    }
    void main() {work(1); }
}
