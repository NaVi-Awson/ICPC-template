template<const int N, typename T, long long inf>
struct dijkstra {
    int n; T dist[N];
    vector<pair<int, T>> to[N];
    struct node {
        int u; T c;
        node (int _u = 0, T _c = 0) {
            u = _u, c = _c;
        }
        bool operator < (const node &b) const {
            return c > b.c;
        }
    } t;
    priority_queue<node> Q;
    void init(int size) {
        n = size;
        for (int i = 1; i <= n; i++) to[i].clear(), dist[i] = inf;
    }
    void dij(int s) {
        Q.push(node(s, dist[s] = 0));
        while (!Q.empty()) {
            t = Q.top(); Q.pop();
            for (auto v : to[t.u]) {
                if (dist[v.first] > t.c+v.second) {
                    dist[v.first] = t.c+v.second;
                    Q.push(node(v.first, t.c+v.second));
                }
            }
            while (!Q.empty() && dist[Q.top().u] != Q.top().c) Q.pop();
        }
    }
} ;
