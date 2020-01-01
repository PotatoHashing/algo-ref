template <typename T>
class LinkCutTree {
 private:
  struct Node {
    bool flip = 0;  // swap children
    // path parent, parent in splay tree, and children
    Node *pp, *p, *c[2];
    // node's value, aggregate value of nodes on the path, node's lazy value,
    // and number of nodes on path/size of splay tree.
    T val = 0, cval = 0, lazy = 0;
    int cnt = 0;
    // size of subtrees (including the root), size of virtual subtrees
    // int siz = 0, vir = 0;
    Node() { pp = p = c[0] = c[1] = 0; }
    // Propogate lazy values.
    void push() {
      if (flip) {
        swap(c[0], c[1]);
        for (auto x : c)
          if (x) x->flip ^= 1;
        flip = 0;
      }
      val += lazy;
      cval += lazy * cnt;
      for (auto x : c)
        if (x) x->lazy += lazy;
      lazy = 0;
    }
    // Aggregate values from children.
    void pull() {
      push();
      cval = val;
      cnt = 1;
      // siz = vir + 1;
      for (auto x : c)
        if (x) x->push(), cval += x->cval, cnt += x->cnt /*, siz += x->siz */;
    }
    // splay tree rotations
    void rot(bool t) {
      Node *y = p, *z = y->p, *&w = c[t];
      if (z) z->c[z->c[1] == y] = this;
      if (w) w->p = y;
      y->c[!t] = w;
      w = y, p = z;
      y->p = this, y->pull();
    }
    // calls push starting from the splay root and then propogates pp down
    void g() {
      if (p) p->g(), pp = p->pp;
      push();
    }
    void splay() {
      g();
      while (p) {
        Node *y = p, *z = y->p;
        bool t1 = (y->c[1] != this);
        bool t2 = z && (z->c[1] != y) == t1;
        if (t2) y->rot(t1);
        rot(t1);
        if (z && !t2) rot(!t1);
      }
      pull();
    }
    Node *access() {
      for (Node *y = 0, *z = this; z; y = z, z = z->pp) {
        z->splay();
        if (z->c[1]) z->c[1]->pp = z, z->c[1]->p = 0;
        if (y) y->p = z;
        // update the size of virtual subtrees
        if (z->c[1])
          z->c[1]->pp = z, z->c[1]->p = 0 /*, z->vir += z->c[1]->siz */;
        if (y) y->p = z /* , z->vir -= y->siz */;
        z->c[1] = y, z->pull();
      }
      splay();
      flip ^= 1;
      return this;
    }
  };
  int n;
  vector<Node> s;
  Node *get(int u) { return s[u].access(); }

 public:
  LinkCutTree(const vector<T> &v) : n(v.size()), s(n) {
    for (int i = 0; i < n; i++) get(i)->val = v[i];
  }
  bool cut(int u, int v) {
    Node *y = get(v), *x = get(u);
    if (x->c[0] != y || y->c[1]) return false;
    x->c[0] = y->p = y->pp = 0;
    x->pull();
    return true;
  }
  bool isConnected(int u, int v) {
    Node *x = get(u), *y = get(v);
    return x == y || x->p;
  }
  bool link(int u, int v) {
    if (isConnected(u, v)) return false;
    Node *x = get(u), *y = get(v);
    x->pp = &s[v];
    // y->vir += x->siz;
    return true;
  }
  void update(int u, int v, T c) { get(v), get(u)->lazy += c; }
  T query(int u, int v) {
    get(v);
    return get(u)->cval;
  }
};