class UnionFind {
  vector<int> rep;

 public:
  UnionFind(int n) : rep(n, -1) {}
  int find(int x) { return rep[x] < 0 ? x : rep[x] = find(rep[x]); }
  bool same_set(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -rep[find(x)]; }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (rep[a] > rep[b]) swap(a, b);
    rep[a] += rep[b], rep[b] = a;
    return true;
  }
};
