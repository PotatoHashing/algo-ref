// example is add to range, find sum of range
template <typename T>
class SegmentTree {
 private:
  int n;
  vector<T> val, lazy;
  const T unit = 0;                   // identity element
  T comb(T a, T b) { return a + b; }  // some associative operation
  void build(vector<T>& a, int p, int l, int r) {
    if (l == r) {
      val[p] = a[l];
    } else {
      int m = (l + r) / 2;
      build(a, 2 * p, l, m), build(a, 2 * p + 1, m + 1, r);
      pull(p);
    }
  }
  void push(int p, int l, int r) {
    val[p] += (r - l + 1) * lazy[p];
    if (l != r) lazy[2 * p] += lazy[p], lazy[2 * p + 1] += lazy[p];
    lazy[p] = 0;
  }
  void pull(int p) { val[p] = comb(val[2 * p], val[2 * p + 1]); }

 public:
  SegmentTree(const vector<T>& a) : n(a.size()), val(4 * n), lazy(4 * n) {
    build(a, 1, 0, n - 1);
  }
  void update(int l, int r, T x) { update(l, r, x, 1, 0, n - 1); }
  void update(int l, int r, T x, int p, int nl, int nr) {
    push(p, nl, nr);
    if (nr < l || r < nl) return;
    if (l <= nl && nr <= r) {
      lazy[p] += x;
      push(p, nl, nr);
    } else {
      int m = (nl + nr) / 2;
      update(l, r, x, 2 * p, nl, m), update(l, r, x, 2 * p + 1, m + 1, nr);
      pull(p);
    }
  }
  T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
  T query(int l, int r, int p, int nl, int nr) {
    push(p, nl, nr);
    if (nr < l || r < nl) return unit;
    if (l <= nl && nr <= r) {
      return val[p];
    } else {
      int m = (nl + nr) / 2;
      return comb(query(l, r, 2 * p, nl, m), query(l, r, 2 * p + 1, m + 1, nr));
    }
  }
};
