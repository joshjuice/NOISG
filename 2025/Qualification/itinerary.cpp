#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")

typedef long long ll;
typedef long double ld;
#define ppf pop_front
#define ppb pop_back
#define pf push_front
#define pb push_back
#define fr first
#define sc second
#define mnto(x,y) x = min(x, (__typeof__(x))y)
#define mxto(x,y) x = max(x, (__typeof__(x))y)
#define setval(arr, x) memset(arr, x, sizeof(arr))

const int MAXN = 3e5+5;
vector<int> g[MAXN];
int n, m, seq[2*MAXN], depth[MAXN], parent[MAXN], freq[MAXN];
bool vis[MAXN], ans[MAXN];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  for (int i = 1; i <= m; ++i) cin >> seq[i];
  function<void(int, int, int)> dfs = [&](int v, int d, int p) {
    depth[v] = d;
    parent[v] = p;
    for (int u : g[v]) if (u != p) dfs(u, d+1, v);
  };
  dfs(1, 0, 1);
  function<vector<int>(int, int)> gp = [&](int u, int v) {
    vector<int> pu, pv;
    while (depth[u] > depth[v]) {
      pu.pb(u);
      u = parent[u];
    }
    while (depth[v] > depth[u]) {
      pv.pb(v);
      v = parent[v];
    }
    while (u != v) {
      pu.pb(u);
      u = parent[u];
      pv.pb(v);
      v = parent[v];
    }
    pu.pb(u);
    reverse(pv.begin(), pv.end());
    for (int x : pv) pu.pb(x);
    return pu;
  };
  function<bool()> mp = [&]() {
    for (int i = 1; i <= n; ++i) freq[i] = vis[i] = 0;
    for (int i = 1; i < m; ++i) {
      vector<int> path = gp(seq[i], seq[i+1]);
      for (int j = 0; j < path.size()-1; ++j) {
        int u = path[j], v = path[j+1];
        int ei = depth[u] > depth[v] ? u : v;
        freq[ei]++;
        if (freq[ei] > 2) return 0;
      }
      for (int x : path) vis[x] = 1;
    }
    return 1;
  };
  function<void(int)> fid = [&](int v) {
    ans[v] = vis[v] = 1;
    for (int u : g[v]) {
      if (vis[u]) continue;
      fid(u);
    }
  };
  function<void()> fi = [&]() {
    for (int i = 1; i <= n; ++i) ans[i] = 0;
    if (!mp()) return;
    vector<int> path = gp(seq[1], seq[m]);
    for (int v : path) fid(v);
  };
  fi();
  for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
}
