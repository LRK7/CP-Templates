// minimum edge weight in the path between any two nodes using binary lifting

int vis[300001];
int level[300001];
int max_power;
map<pair<int, int>, int> edges;

pair<int, int> kth_parent_and_minm(int node, int k, vector<vector<int>> &parent, vector<vector<int>> &mini) {
    int minm = 1e9 + 7;
    for (int i = 0; i < max_power; ++i) {
        if (k & (1 << i)) {
            minm = min(minm, mini[node][i]);
            node = parent[node][i];
            if (node == -1) {
                break;
            }
        }
    }
    return {node, minm};
}

pair<int, int> LCA_and_minm(int nodeA, int nodeB, vector<vector<int>> &parent, vector<vector<int>> &mini) {
    int minm1 = 1e9 + 7, minm2 = 1e9 + 7;
    if (level[nodeA] > level[nodeB]) {
        pair<int, int> p = kth_parent_and_minm(nodeA, level[nodeA] - level[nodeB], parent, mini);
        nodeA = p.first;
        minm1 = p.second;
    }
    else {
        pair<int, int> p = kth_parent_and_minm(nodeB, level[nodeB] - level[nodeA], parent, mini);
        nodeB = p.first;
        minm2 = p.second;
    }
    if (nodeA == nodeB) {
        return {nodeA, min(minm1, minm2)};
    }
    for (int i = max_power - 1; i >= 0; --i) {
        if (parent[nodeA][i] != parent[nodeB][i]) {
            minm1 = min(minm1, mini[nodeA][i]);
            minm2 = min(minm2, mini[nodeB][i]);
            nodeA = parent[nodeA][i];
            nodeB = parent[nodeB][i];
        }
    }
    minm1 = min(minm1, mini[nodeA][0]);
    minm2 = min(minm2, mini[nodeB][0]);
    return {parent[nodeA][0], min(minm1, minm2)};
}

int dis(int nodeA, int nodeB, vector<vector<int>> &parent, vector<vector<int>> &mini) {
    int nodeLCA = LCA_and_minm(nodeA, nodeB, parent, mini).first;
    return level[nodeA] + level[nodeB] - 2 * level[nodeLCA];
}

void dfs(int node, int p, int curr_level, vector<vector<int>> &g, vector<vector<int>> &parent, vector<vector<int>> &mini) {
    vis[node] = 1;
    level[node] = curr_level;
    parent[node][0] = p;
    if (p != -1) {
        mini[node][0] = edges[ {node, p}];
    }
    for (auto x : g[node]) {
        if (!vis[x]) {
            dfs(x, node, curr_level + 1, g, parent, mini);
        }
    }
    return;
}

void solve() {
    int n, m;
    cin >> n >> m;
    max_power = log2(n) + 5;
    vector<vector<int>> g(n + 1);
    vector<vector<int>> parent(n + 1, vector<int> (max_power, -1));
    vector<vector<int>> mini(n + 1, vector<int> (max_power, 1e9 + 7));
    memset(vis, 0, sizeof(vis));
    memset(level, 0, sizeof(level));
    for (int i = 0; i < m; ++i) {
        int x, y, val;
        cin >> x >> y >> val;
        g[x].push_back(y);
        g[y].push_back(x);
        edges[ {x, y}] = val;
        edges[ {y, x}] = val;
    }
    dfs(1, -1, 0, g, parent, mini);
    for (int i = 1; i < max_power; ++i) {
        for (int node = 2; node <= n; ++node) {
            int intermediate = parent[node][i - 1];
            if (intermediate != -1) {
                parent[node][i] = parent[intermediate][i - 1];
                mini[node][i] = min(mini[node][i - 1], mini[intermediate][i - 1]);
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int nodeA, nodeB;
        cin >> nodeA >> nodeB;
        cout << LCA_and_minm(nodeA, nodeB, parent, mini).second << nline;
    }
    return;
}
