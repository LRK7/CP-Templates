vector<int> getDis(int src, int n, vector<vector<int>> &adj) {
    vector<int> dist(n, 0), vis(n, 0);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    vis[src] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                dist[v] = dist[u] + 1;
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    return dist;
}
