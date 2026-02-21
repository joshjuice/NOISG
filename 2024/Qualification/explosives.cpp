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

#define supply(i) get<1>(events[i])
#define loc(i) get<0>(events[i])

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, c;
  cin >> n >> c;
  vector<tuple<int, int>> events(n<<1|1);
  for (int i = 1; i <= n<<1; ++i) {
    cin >> loc(i);
    supply(i) = (i > n ? -1 : 1);
  }
  sort(events.begin(), events.end());
  for (int i = 1; i <= n<<1; ++i) supply(i) += supply(i-1);
  vector<int> ans;
  int carry = 0, cost = 0;
  bool changed = 1;
  do {
    changed = 0;
    for (int i = 0; i <= n<<1; ++i) {
      int target = min(c, max(0, supply(i)));
      if (target != carry) ans.pb(i);
      carry = target;
      supply(i) -= carry;
      if (carry) {
        changed = 1;
        cost += abs(loc(i+1) - loc(i));
      }
    }
  } while (changed);
  do {
    changed = 0;
    for (int i = n<<1; i >= 0; --i) {
      int target = min(c, max(0, -supply(i)));
      if (target != carry) ans.pb(i+1);
      carry = target;
      supply(i) += carry;
      if (carry) {
        changed = 1;
        cost += abs(loc(i+1) - loc(i));
      }
    }
  } while (changed);
  cout << cost << '\n';
  for (int idx : ans) cout << loc(idx) << ' ';
}
