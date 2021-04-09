template<const int N, const int M, typename Type>
struct dinic {
    struct tt {int to, next; Type cap; } edge[M<<1];
    int path[N], top, S, T;
    int sta[N], cur[N], dist[N];
    queue<int> Q;
    const Type inf = numeric_limits<Type>::max();
    
    dinic(const int s, const int t) {
        memset(path, top = -1, sizeof(path));
        S = s, T = t;
    }
    bool bfs() {
        memset(dist, -1, sizeof(dist));
        Q.push(S); dist[S] = 1;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int i = path[u], v; ~i; i = edge[i].next)
                if (dist[v = edge[i].to] == -1 && edge[i].cap > 0)
                    Q.push(v), dist[v] = dist[u]+1;
        }
        return dist[T] != -1;
    }
    Type maxflow() {
        Type totflow = 0;
        while (bfs()) {
            int u = S; top = 0; memcpy(cur, path, sizeof(cur));
            while (1) {
                if (u == T) {
                    int loc = -1; Type minflow = inf;
                    for (int i = 1; i <= top; i++) if (edge[sta[i]].cap < minflow) minflow = edge[sta[loc = i]].cap;
                    for (int i = 1; i <= top; i++) edge[sta[i]].cap -= minflow, edge[sta[i]^1].cap += minflow;
                    totflow += minflow; u = edge[sta[loc]^1].to, top = loc-1;
                }
                for (int &i = cur[u], v; ~i; i = edge[i].next)
                    if (dist[v = edge[i].to] == dist[u]+1 && edge[i].cap > 0) {
                        sta[++top] = i, u = v; break;
                    }
                if (cur[u] == -1) {
                    if (top == 0) break;
                    dist[u] = -1; u = edge[sta[top--]^1].to; 
                } 
            }
        }
        return totflow;
    }
    void add(int u, int v, Type c) {
        edge[++top] = (tt){v, path[u], c}; path[u] = top;
        edge[++top] = (tt){u, path[v], 0}; path[v] = top;
    }
} ;
