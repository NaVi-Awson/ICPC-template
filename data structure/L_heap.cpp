template<typename T, const int N>
struct L_heap {
    int ch[N][2], dist[N], pos, root, cnt;
    T key[N];
    queue<int>mem;
    int newnode(T x) {
        int o;
        if (!mem.empty()) o = mem.front(), mem.pop();
        else o = ++pos;
        ch[o][0] = ch[o][1] = dist[o] = 0;
        key[o] = x;
        return o;
    }
    int merge(int a, int b) {
        if (!a || !b) return a+b;
        if (key[a] > key[b]) swap(a, b); // change the '<'
        ch[a][1] = merge(ch[a][1], b);
        if (dist[ch[a][0]] < dist[ch[a][1]]) swap(ch[a][0], ch[a][1]);
        dist[a] = dist[ch[a][1]]+1;
        return a;
    }
    T top() {return key[root]; }
    void push(T x) {root = merge(root, newnode(x)); ++cnt; }
    void pop() {mem.push(root); root = merge(ch[root][0], ch[root][1]); --cnt; }
    bool empty() {return !cnt; }
} ;
