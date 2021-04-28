template<const int N, const int M, typename Ty>
struct MCMF {// the maxflow: flow, the mincost with max flow: ans
    int n, m, S, T;
    struct tt {int to, next; Ty cap, cost; } edge[M<<1];
    int path[N], top, vis[N], pre[N];
    Ty dist[N], inf, flow, ans;
    queue<int> Q;
    MCMF (const int s, const int t) {
        memset(path, top = -1, sizeof(path));
        flow = ans = 0;
        S = s, T = t;
    }
    void add(int u, int v, Ty w, Ty f) {// w: flow, f: cost
        edge[++top] = (tt){v, path[u], w, f}; path[u] = top;
        edge[++top] = (tt){u, path[v], 0, -f}; path[v] = top;
    }
    bool SPFA() {
        memset(dist, 127/3, sizeof(dist)); dist[S] = 0; inf = dist[T];
        memset(vis, 0, sizeof(vis)); vis[S] = 1; Q.push(S);
        while (!Q.empty()) {
            int u = Q.front(), v; Q.pop(); vis[u] = 0;
            for (int i = path[u]; ~i; i = edge[i].next)
                if (edge[i].cap && dist[v = edge[i].to] > dist[u]+edge[i].cost) {
                    dist[v] = dist[u]+edge[i].cost; pre[v] = i;
                    if (!vis[v]) Q.push(v), vis[v] = 1;
                }
        }
        if (dist[T] == inf) return 0;
        Ty minn = inf;
        for (int u = T; u != S; u = edge[pre[u]^1].to) minn = min(minn, edge[pre[u]].cap);
        for (int u = T; u != S; u = edge[pre[u]^1].to) edge[pre[u]].cap -= minn, edge[pre[u]^1].cap += minn;
        flow += minn;
        ans += minn*dist[T];
        return 1;
    }
    Ty mincost() {while (SPFA()); return ans; }
} ;
