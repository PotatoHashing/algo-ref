template <typename T>
class Dijkstra {
  const T INF = 1e9;  // set as appropriate
  using pti = pair<T, int>;

 private:
  int n;
  vector<vector<pti>> g;

 public:
  Dijkstra(int n) : n(n), g(n) {}
  void addEdge(int u, int v, T w, bool isDir = false) {
    assert(w >= 0);
    g[u].push_back({w, v});
    if (!isDir) g[v].push_back({w, u});
  }
  vector<T> solve(int s) {
    vector<T> dist(n, INF);
    dist[s] = 0;
    vector<int> vis(n, false);
    priority_queue<pti, vector<pti>, greater<pti>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) continue;
      vis[u] = true;
      for (auto [w, v] : g[u]) {
        T d = dist[u] + w;
        if (d < dist[v]) pq.push({dist[v] = d, v});
      }
    }
    return dist;
  }
};