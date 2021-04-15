/* N(x): the subset of v which is near u after x in the sequence
 * nxt_x = minloc{N(x)}, if nxt_y = x & |N(x)|+1 <= N(y) then {x}+N(x) is not the maximum clique
 * color(): coloring the graph, and cnt_color = max_clique_size
 * independence(): if indep[x] then {x}+N(x) is in the minimal clique covering. cnti means maximal independent set
 */
template<const int N>
struct chordalgraph {// label: 1..n
    vector<int> to[N], lst[N];
    map<int, int> mp[N];
    int vis[N], seq[N], rk[N], label[N];// seq[1..n]: perfect sequence, rk[seq[x]] = x
    int n;
    int tmp[N], col[N], cntc, clique;// col[node], cntc = clique
    int indep[N], cnti;// indep[node]
    chordalgraph(int n) : n(n) {};
    void init() {for (int i = 1; i <= n; i++) to[i].clear(), mp[i].clear(); }
    void add(int u, int v) {
        to[u].push_back(v), to[v].push_back(u);
        mp[u][v] = 1, mp[v][u] = 1;
    }
    bool mcs() {// return judgement & get sequence
        lst[0].clear();
        for (int i = 1; i <= n; i++)
            vis[i] = label[i] = 0, lst[i].clear(), lst[0].push_back(i);
        int best = 0;
        clique = 0;
        for (int i = n; i; i--) {
            int flag = 0, loc;
            while (!flag) {
                for (int j = lst[best].size()-1; j >= 0; j--)
                    if (!vis[lst[best][j]]) {
                        loc = lst[best][j];
                        flag = 1;
                        break;
                    } else lst[best].pop_back();
                if (!flag) --best;
            }
            seq[i] = loc, rk[loc] = i, vis[loc] = 1;
            for (int v : to[loc])
                if (!vis[v]) {
                    lst[++label[v]].push_back(v);
                    best = max(best, label[v]);
                    clique = max(clique, best+1);
                }
        }
        for (int i = 1; i <= n; i++) {
            int loc = -1, u = seq[i];
            for (int v : to[u]) {
                if (rk[v] < rk[u]) continue;
                if (loc == -1 || rk[loc] > rk[v]) loc = v;
            }
            for (int v : to[u]) {
                if (rk[v] < rk[u]) continue;
                if (v != loc && mp[loc].count(v) == 0) return false;
            }
        }
        return true;
    }
    int color() {
        memset(tmp, -1, sizeof(tmp));
        cntc = 0;
        for (int i = n; i >= 1; i--) {
            int u = seq[i], flag = 0;
            for (int v : to[u])
                if (rk[v] > rk[u]) tmp[col[v]] = i;
            for (int j = 1; j <= cntc; j++)
                if (tmp[j] != i) {col[u] = j; flag = 1; break; }
            if (!flag) col[u] = ++cntc;
        }
        return cntc;
    }
    int independence() {
        cnti = 0;
        for (int i = 1; i <= n; i++) {
            int u = seq[i], t = 0;
            for (int v : to[u])
                if (rk[v] < rk[u]) t |= indep[v];
            cnti += (indep[u] = t^1);
        }
        return cnti;
    }
} ;
