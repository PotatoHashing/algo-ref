template <typename T>
class Fenwick {
 private:
  int n;
  vector<T> v;

 public:
  Fenwick(int n) : n(n), v(n) {}
  Fenwick(const vector<T>& a) : n(a.size()), v(n) {
    for (int i = 0; i < n; i++) {
      v[i] = a[i];
      int j = i | (i + 1);
      if (j < n) a[j] += a[i];
    }
  }
  void update(int pos, T dif) {  // a[pos] += dif
    for (; pos < n; pos |= pos + 1) v[pos] += dif;
  }
  T query(int pos) {  // sum of values in [0, pos)
    T res = 0;
    for (; pos > 0; pos &= pos - 1) res += v[pos - 1];
    return res;
  }
  T query(int lb, int ub) {  // sum of values in [lb, rb)
    return query(rb) - query(lb);
  }
  int lower_bound(T sum) {  // min pos st sum of [0, pos] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= n && v[pos + pw - 1] < sum) pos += pw, sum -= v[pos - 1];
    }
    return pos;
  }
};
