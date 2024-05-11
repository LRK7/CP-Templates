// Binary lifting
// Kth parent of a node in a tree
// LCA of any two nodes in a tree
// Distance between any two nodes in a tree

int vis[200001];
int level[200001];
int max_power;

int kth_parent(int node, int k, vector<vector<int>> &parent) {
    for (int i = 0; i < max_power; ++i) {
        if (k & (1 << i)) {
            node = parent[node][i];
            if (node == -1) {
                break;
            }
        }
    }
    return node;
}

int LCA(int nodeA, int nodeB, vector<vector<int>> &parent) {
    if (level[nodeA] > level[nodeB]) {
        nodeA = kth_parent(nodeA, level[nodeA] - level[nodeB], parent);
    }
    else {
        nodeB = kth_parent(nodeB, level[nodeB] - level[nodeA], parent);
    }
    if (nodeA == nodeB) {
        return nodeA;
    }
    for (int i = max_power - 1; i >= 0; --i) {
        if (parent[nodeA][i] != parent[nodeB][i]) {
            nodeA = parent[nodeA][i];
            nodeB = parent[nodeB][i];
        }
    }
    return parent[nodeA][0];
}

int dis(int nodeA, int nodeB, vector<vector<int>> &parent) {
    int nodeLCA = LCA(nodeA, nodeB, parent);
    return level[nodeA] + level[nodeB] - 2 * level[nodeLCA];
}

void dfs(int node, int p, int curr_level, vector<vector<int>> &g, vector<vector<int>> &parent) {
    vis[node] = 1;
    level[node] = curr_level;
    parent[node][0] = p;
    for (auto x : g[node]) {
        if (!vis[x]) {
            dfs(x, node, curr_level + 1, g, parent);
        }
    }
    return;
}

void solve() {
    int n, q;
    cin >> n >> q;
    max_power = log2(n) + 5;
    vector<vector<int>> g(n + 1);
    vector<vector<int>> parent(n + 1, vector<int> (max_power, -1));
    memset(vis, 0, sizeof(vis));
    memset(level, 0, sizeof(level));
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1, -1, 0, g, parent);
    for (int i = 1; i < max_power; ++i) {
        for (int node = 2; node <= n; ++node) {
            int intermediate = parent[node][i - 1];
            if (intermediate != -1) {
                parent[node][i] = parent[intermediate][i - 1];
            }
        }
    }
    while (q--) {
        int nodeA, nodeB;
        cin >> nodeA >> nodeB;
        cout << dis(nodeA, nodeB, parent) << nline;
    }
    return;
}
