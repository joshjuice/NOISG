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

struct Monster {
  int position, hp;
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, k;
  ll r = 0;
  cin >> n >> k;
  vector<Monster> m(n);
  vector<int> x(k);
  for (int i = 0; i < n; ++i) cin >> m[i].position >> m[i].hp;
  for (int i = 0; i < k; ++i) cin >> x[i];
  sort(m.begin(), m.end(), [](const Monster &a, const Monster &b) {
    return a.position < b.position;
  });
  sort(x.begin(), x.end());
  set<int> e;
  for (int i = 0; i < n; ++i) {
    auto rb = lower_bound(x.begin(), x.end(), m[i].position);
    int rd = abs(*rb - m[i].position);
    if (rb == x.begin()) {
      if (m[i].hp < rd) r += m[i].hp;
      else {
        r += rd;
        e.insert(*rb);
      }
    } else if (rb == x.end()) {
      auto lb = x.rbegin();
      int rd = abs(*lb - m[i].position);
      if (m[i].hp < rd) r += m[i].hp;
      else {
        r += rd;
        e.insert(*lb);
      }
    } else {
      auto lb = rb-1;
      int ld = abs(*lb - m[i].position);
      if (m[i].hp < ld && m[i].hp < rd) r += m[i].hp;
      else if (ld < rd) {
        r += ld;
        e.insert(*lb);
      } else if (rd < ld) {
        r += rd;
        e.insert(*rb);
      } else {
        if (e.find(*lb) != e.end()) r += ld;
        else {
          e.insert(*rb);
          r += rd;
        }
      }
    }
  }
  cout << r + e.size();
}
