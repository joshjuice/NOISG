#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC optimize("Ofast")

#define int long long
#define rep(x, a, b) for(auto x=a;(a<b?x<b:x>b);(a<b?x++:x--))
#define all(a) a.begin(), a.end()
#define ppf pop_front
#define ppb pop_back
#define pf push_front
#define pb push_back
#define fr first
#define sc second
#define ii pair<int, int>
#define iii tuple<int, int, int>
#define vc vector
#define sz(a) a.size()
#define mnto(x,y) x = min(x, (__typeof__(x))y)
#define mxto(x,y) x = max(x, (__typeof__(x))y)
#define setval(arr, x) memset(arr, x, sizeof(arr))

template<typename T>
using vv = vc<vc<T>>;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct ST {
  int n;
  vc<int> tree, lazy;
  ST(int size) {
    n = 1;
    while (n < size) n <<= 1;
    tree.assign(n*2, INT_MAX);
    lazy.assign(n*2, 0);
  }
  void build(const vc<int> &v) {
    rep(i, 0, sz(v)) tree[n+i] = v[i];
    rep(i, n-1, 0) tree[i] = min(tree[2*i], tree[2*i+1]);
  }
  void push(int node) {
    if (lazy[node] == 0) return;
    tree[node] += lazy[node];
    if (node < n) {
      lazy[2*node] += lazy[node];
      lazy[2*node+1] += lazy[node];
    }
    lazy[node] = 0;
  }
  void update(int node, int l, int r, int ql, int qr, int val) {
    push(node);
    if (r < ql || l > qr) return;
    if (ql <= l && r <= qr) {
      lazy[node] += val;
      push(node);
      return;
    }
    int mid = (l + r) >> 1;
    update(2*node, l, mid, ql, qr, val);
    update(2*node+1, mid+1, r, ql, qr, val);
    tree[node] = min(tree[2*node], tree[2*node+1]);
  }
  void range_add(int l, int r, int val) {
    update(1, 0, n-1, l, r, val);
  }
  int query(int node, int l, int r) {
    push(node);
    if (tree[node] != 0) return -1;
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int left = query(2*node, l, mid);
    if (left != -1) return left;
    return query(2*node+1, mid+1, r);
  }
};

vc<int> topo(const vv<int> &out_edges, vc<int> in_deg) {
  int n = sz(out_edges);
  vc<int> order;
  queue<int> q;
  rep(i, 0, n) if (in_deg[i] == 0) q.push(i);
  while (sz(q)) {
    int u = q.front();
    q.pop();
    order.pb(u);
    for (int v : out_edges[u]) {
      in_deg[v]--;
      if (in_deg[v] == 0) q.push(v);
    }
  }
  return order;
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, m;
  cin >> n >> m;
  vc<ii> edges(m);
  vv<int> out_edges(n);
  vc<int> in_deg(n, 0);
  rep(i, 0, m) {
    int x, y;
    cin >> x >> y;
    x--; y--;
    edges[i] = {x, y};
    out_edges[x].pb(y);
    in_deg[y]++;
  }
  vc<int> topo_order = topo(out_edges, in_deg);
  vc<int> inv_order(n);
  rep(i, 0, n) inv_order[topo_order[i]] = i;
  for (auto &p : edges) {
    p.fr = inv_order[p.fr];
    p.sc = inv_order[p.sc];
  }
  ST st(n);
  st.build(vc<int>(n, n-1));
  vc<int> a(n, n), b(n, -1), ord(n, -2);
  rep(i, 0, m) {
    auto [x, y] = edges[i];
    if (a[x] > y) {
      st.range_add(y, a[x]-1, -1);
      a[x] = y;
    }
    if (b[y] < x) {
      st.range_add(b[y]+1, x, -1);
      b[y] = x;
    }
    int zi;
    while ((zi = st.query(1, 0, st.n-1)) != -1) {
      ord[zi] = i;
      st.range_add(zi, zi, 1);
    }
  }
  rep(i, 0, n) cout << ord[inv_order[i]]+1 << ' ';
}
