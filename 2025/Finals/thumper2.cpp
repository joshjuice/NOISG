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

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, m;
  cin >> n >> m;
  vector<ll> X(n), Y(n);
  for (int i = 0; i < n; ++i) {
    int r, c;
    cin >> r >> c;
    X[i] = r + c;
    Y[i] = r - c;
  }
  vector<int> t(m);
  for (int i = 0; i < m; ++i) cin >> t[i], t[i]--;
  vector<ll> vx = X, vy = Y;
  sort(vx.begin(), vx.end());
  sort(vy.begin(), vy.end());
  vx.erase(unique(vx.begin(), vx.end()), vx.end());
  vy.erase(unique(vy.begin(), vy.end()), vy.end());
  int ux = vx.size(), uy = vy.size();
  vector<int> cx(n), cy(n);
  for (int i = 0; i < n; ++i) {
    cx[i] = lower_bound(vx.begin(), vx.end(), X[i]) - vx.begin();
    cy[i] = lower_bound(vy.begin(), vy.end(), Y[i]) - vy.begin();
  }
  vector<ll> k(n, 0), cntx(ux, 0), cnty(uy, 0);
  for (int i = 0; i < m; ++i) k[t[i]]++;
  for (int i = 0; i < n; ++i) {
    cntx[cx[i]] += k[i];
    cnty[cy[i]] += k[i];
  }
  vector<ll> prex(ux+1, 0), prey(uy+1, 0);
  for (int i = 0; i < ux; ++i) prex[i+1] = prex[i] + cntx[i];
  for (int i = 0; i < uy; ++i) prey[i+1] = prey[i] + cnty[i];
  ll totx = prex[ux], toty = prey[uy];
  vector<ll> rf(n), cf(n);
  for (int i = 0; i < n; ++i) {
    ll plusx = prex[cx[i]];
    ll minusx = totx - prex[cx[i]+1];
    ll xf = X[i] + 2 * (plusx - minusx);
    ll plusy = prey[cy[i]];
    ll minusy = toty - prey[cy[i]+1];
    ll yf = Y[i] + 2 * (plusy - minusy);
    cout << (xf + yf) / 2 << ' ' << (xf - yf) / 2 << '\n';
  }
}
