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
  int n, d;
  cin >> n >> d;
  int a[n];
  for (int i = 0; i < n; ++i) cin >> a[i];
  int steps = 0, maxduck = 0;
  for (int i = n-1; i > 0; --i) {
    if (a[i] - maxduck >= 0) {
      steps += i * (a[i] - maxduck);
      mxto(maxduck, a[i]);
    }
  }
  cout << steps;
}
