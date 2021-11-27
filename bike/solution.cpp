#include <bits/stdc++.h>
using namespace std;

const int N   = 1e5 + 5;
const int INF = 2e9;

int pset[N];
int tin[N], tout[N];
vector<pair<int, int>> children[N];
int parent[N];

int n, m;
int h[N];
vector<pair<int, pair<int, int>>> elist;
vector<int> treeAdj[N];

int ans[N];

int finds(int x) { return pset[x] == x ? x : pset[x] = finds(pset[x]); }

void join(int x, int y) {
    x = finds(x);
    y = finds(y);
    if (x != y) {
        pset[x] = y;
    }
}

void dfs(int now, int prv) {
    parent[now] = prv;

    static int cntr = 0;
    tin[now]        = ++cntr;
    for (int nex : treeAdj[now]) {
        if (nex == prv) continue;
        dfs(nex, now);

        children[now].push_back({tin[nex], nex});
    }
    tout[now] = cntr;
}

void read() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        elist.push_back({abs(h[u] - h[v]), {u, v}});
    }
}

void prepare() {
    for (int i = 1; i <= n; i++) {
        pset[i] = i;
        ans[i]  = INF;
    }
    sort(elist.begin(), elist.end());
}

void mark(int u, int v, int w) {
    int realU = u;
    u         = finds(u);

    while (!(tin[u] <= tin[v] && tin[v] <= tout[u])) {
        ans[u] = min(ans[u], w);
        join(u, parent[u]);
        u = finds(u);
    }

    pair<int, int> dummy = {tin[realU], INF};
    int idx = upper_bound(children[u].begin(), children[u].end(), dummy) - children[u].begin();
    idx--;
    int u2 = children[u][idx].second;
    // already higher than LCA
    if (tin[u2] <= tin[v] && tin[v] <= tout[u2]) {
        return;
    }

    ans[u] = min(ans[u], w);
    if (u != 1) {
        join(u, parent[u]);
    }
}

void work() {
    vector<pair<int, pair<int, int>>> notInTree;

    for (int i = 0; i < elist.size(); i++) {
        auto e = elist[i];
        int u  = e.second.first;
        int v  = e.second.second;

        if (finds(u) != finds(v)) {
            treeAdj[u].push_back(v);
            treeAdj[v].push_back(u);
            join(u, v);
        } else {
            notInTree.push_back(e);
        }
    }

    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        pset[i] = i;
    }

    for (auto e : notInTree) {
        int w = e.first;
        int u = e.second.first;
        int v = e.second.second;

        mark(u, v, w);
        mark(v, u, w);
    }

    for (int i = 1; i <= n; i++) {
        int v = ans[i];
        if (v == INF) v = -1;
        printf("%d%c", v, " \n"[i == n]);
    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}
