#include <bits/stdc++.h>
using namespace std;

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

typedef pair<ll, int> pli;

const ll INF = (1ll<<62);

ll egcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = (a >= 0 ? 1 : -1);
    y = 0;
    return llabs(a);
  }
  ll x1, y1;
  ll g = egcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
}

ll modinv(ll a, ll mod) {
  ll x, y;
  ll g = egcd(a, mod, x, y);
  if (g != 1) return -1;
  x %= mod;
  if (x < 0) x += mod;
  return x;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  string maxpossible = "99999";
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(m);
  for (int i = 0; i < m; ++i) cin >> a[i];
  vector<ll> c(m);
  for (int i = 0; i < m; ++i) cin >> c[i];
  string x;
  cin >> x;
  vector<string> vs(n);
  for (int i = 0; i < n; ++i) cin >> vs[i];
  vector<int> g(m), p(m);
  for (int i = 0; i < m; ++i) {
    g[i] = std::gcd(a[i], k);
    p[i] = k / g[i];
    if (p[i] == 0) p[i] = 1;
  }
  int totalstates = 1;
  for (int i = 0; i < m; ++i) totalstates *= p[i];
  vector<int> mul(m);
  mul[0] = 1;
  for (int i = 1; i < m; ++i) mul[i] = mul[i-1] * p[i-1];
  vector<ll> dist(totalstates, INF);
  priority_queue<pli, vector<pli>, greater<pli>> pq;
  dist[0] = 0;
  pq.push({0, 0});
  vector<int> digits(m), ndig(m);
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d != dist[u]) continue;
    int tmp = u;
    for (int j = 0; j < m; ++j) {
      if (p[j] == 1) digits[j] = 0;
      else {
        digits[j] = tmp % p[j];
        tmp /= p[j];
      }
    }
    for (int l = 0; l < m; ++l) for (int r = l; r < m; ++r) {
      for (int j = 0; j < m; ++j) ndig[j] = digits[j];
      for (int j = l; j <= r; ++j) {
        if (p[j] == 1) ndig[j] = 0;
        else {
          ndig[j]++;
          if (ndig[j] >= p[j]) ndig[j] -= p[j];
        }
      }
      int nid = 0;
      for (int j = 0; j < m; ++j) nid += ndig[j] * mul[j];
      ll w = c[l] + c[r];
      if (dist[nid] > d + w) {
        dist[nid] = d + w;
        pq.push({dist[nid], nid});
      }
    }
  }
  vector<ll> a_red(m), k_red(m), inv_a_red(m, -1);
  for (int j = 0; j < m; ++j) {
    if (p[j] == 1) {
      a_red[j] = 0;
      k_red[j] = 1;
      inv_a_red[j] = -1;
    } else {
      a_red[j] = a[j] / g[j];
      k_red[j] = k / g[j];
      inv_a_red[j] = modinv(a_red[j] % k_red[j], k_red[j]);
    }
  }
  for (int i = 0; i < n; ++i) {
    vector<int> dreq(m);
    bool ok = 1;
    for (int j = 0; j < m; ++j) {
      int xv = x[j] - '0';
      int vv = vs[i][j] - '0';
      int dj = (xv - vv) % k;
      if (dj < 0) dj += k;
      dreq[j] = dj;
      if (dreq[j] % g[j] != 0) {
        ok = 0;
        break;
      }
    }
    if (!ok) {
      cout << -1 << '\n';
      continue;
    }
    int id = 0;
    for (int j = 0; j < m; ++j) {
      int sj = 0;
      if (p[j] != 1) {
        ll dprime = dreq[j] / g[j];
        ll inv = inv_a_red[j];
        sj = (int)((dprime % k_red[j]) * inv % k_red[j]);
      }
      id += sj * mul[j];
    }
    if (dist[id] >= INF / 4) cout << -1 << '\n';
    else cout << dist[id] << '\n';
  }
}
