// example is min
template <typename T>
class SparseTable {
 private:
  int n;
  vector<vector<T>> st;
  T comb(T a, T b) { return min(a, b); }

 public:
  SparseTable(const vector<T>& a) : n(a.size()), st({a}) {
    for (int w = 2; w < n; w <<= 1) {
      int hw = w / 2;
      vector<T> nex, pre = st.back();
      for (int i = 0; i + w <= n; i++) {
        nex.push_back(comb(pre[i], pre[i + hw]));
      }
      st.push_back(nex);
    }
  }
  T query(int l, int r) {  //[l, r)
    int dep = 31 - __builtin_clz(r - l);
    return comb(st[dep][l], st[dep][r - (1 << dep)]);
  }
};