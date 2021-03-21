template<const int N, typename T, long long inf>// the MAX size of array, type of dist[], the value of infty
struct dijkstra {
    int n; T dist[N+5];
    vector<pair<int, T>> to[N+5];
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
    void init(int size) {// the number of nodes
        n = size;
        for (int i = 0; i <= n; i++) to[i].clear(), dist[i] = inf;
    }
    void dij(int s) {// source
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
