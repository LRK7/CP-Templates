bool is_bipartite(int node, vector<vector<int>> &g, vector<int> &col, int color) {
    col[node] = color;
    int opp_color = (color == 1) ? 2 : 1;
    for (auto x : g[node]) {
        if (col[x] == 0 && !is_bipartite(x, g, col, opp_color)) {
            return false;
        }
        if (col[x] != opp_color) {
            return false;
        }
    }
    return true;
}
