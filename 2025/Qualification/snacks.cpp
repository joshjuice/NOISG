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

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, q;
  cin >> n >> q;
  ll sum = 0;
  map<int, ll> m;
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    m[a]++;
    sum += a;
  }
  cout << sum << '\n';
  while (q--) {
    int l, r, x, d = 0;
    cin >> l >> r >> x;
    auto it = m.lower_bound(l);
    while (it != m.upper_bound(r)) {
      d += it->sc;
      sum += (x - it->fr) * (it->sc);
      it = m.erase(it);
    }
    m[x] += d;
    cout << sum << '\n';
  }
}
