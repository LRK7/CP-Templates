vector<int> getPath(int src, int dest, int n, vector<vector<int>> &adj) {
    auto bfs = [&](int src) {
        vector<int> vis(n, 0), from(n, -1);
        queue<int> q;
        q.push(src);
        vis[src] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    from[v] = u;
                    q.push(v);
                }
            }
        }
        return from;
    };
    vector<int> from = bfs(src), path;
    for (int node = dest; node != -1; node = from[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}
