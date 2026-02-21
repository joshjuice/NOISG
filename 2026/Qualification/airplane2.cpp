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

#define int ll

int h, w, k;
vector<int> c;

bool check(int x) {
  int currow = 1;
  for (int i = 1; i < k; ++i) {
    if (abs(c[i] - c[i-1]) >= x) continue;
    currow += x - abs(c[i] - c[i-1]);
    if (currow > h) return 0;
  }
  return 1;
}

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> h >> w >> k;
  c.resize(k);
  for (int i = 0; i < k; ++i) cin >> c[i];
  sort(c.begin(), c.end());
  int lo = 1, hi = h+w, ans = -1;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) {
      lo = mid + 1;
      ans = mid;
    } else hi = mid - 1;
  }
  cout << ans;
}
