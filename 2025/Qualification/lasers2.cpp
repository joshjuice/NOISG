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

const int MAXN = 2005;
int h, w, k;
vector<pair<int, int>> leftseg[MAXN], rightseg[MAXN];
int dp1[MAXN][MAXN], dp2[MAXN][MAXN];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> h >> w >> k;
  int maxlen = 0;
  for (int i = 0; i < h; ++i) {
    int l, r, c;
    cin >> l >> r >> c;
    for (int j = l; j <= r; ++j) {
      leftseg[j].pb({l, c});
      rightseg[j].pb({r, c});
    }
    mxto(maxlen, r-l+1);
  }
  for (int i = 1; i <= w; ++i) {
    sort(leftseg[i].rbegin(), leftseg[i].rend());
    sort(rightseg[i].begin(), rightseg[i].end());
  }
  for (int i = 0; i <= w+1; ++i) for (int j = 0; j <= w; ++j) dp1[i][j] = dp2[i][j] = k+1;
  dp1[0][0] = dp2[w+1][0] = 0;
  for (int i = 1; i <= w; ++i) {
    int p = 0, sum = 0;
    if (leftseg[i].empty()) dp1[i][1] = 0;
    for (int j = i-1; j >= 0; --j) {
      while (p < leftseg[i].size() && leftseg[i][p].fr > j) {
        sum += leftseg[i][p].sc;
        if (sum > k) break;
        p++;
      }
      if (sum > k) break;
      for (int a = 1; a <= i; ++a) mnto(dp1[i][a], dp1[j][a-1] + sum);
    }
  }
  for (int i = w; i > 0; --i) {
    int p = 0, sum = 0;
    if (rightseg[i].empty()) dp2[i][1] = 0;
    for (int j = i+1; j <= w+1; ++j) {
      while (p < rightseg[i].size() && rightseg[i][p].fr < j) {
        sum += rightseg[i][p].sc;
        if (sum > k) break;
        p++;
      }
      if (sum > k) break;
      for (int a = 1; a <= w-i+1; ++a) mnto(dp2[i][a], dp2[j][a-1] + sum);
    }
  }
  for (int i = 1; i <= w; ++i) for (int j = 0; j <= w; ++j) mnto(dp1[i][j], dp1[i-1][j]);
  for (int i = w; i >= 0; --i) for (int j = 0; j <= w; ++j) mnto(dp2[i][j], dp2[i+1][j]);
  int lo = 0, hi = w;
  while (lo < hi) {
    int m = (lo + hi + 1) >> 1;
    bool ok = 0;
    for (int i = 0; i <= w - maxlen; ++i) {
      int j = i + maxlen + 1;
      for (int a = 0; a <= m; ++a) {
        if (dp1[i][a] + dp2[j][m-a] <= k) {
          ok = 1;
          break;
        }
      }
      if (ok) break;
    }
    if (ok) lo = m;
    else hi = m-1;
  }
  cout << lo;
}
