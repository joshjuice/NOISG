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

const int LOG = 20;
const int MAXN = 5e5+5;

int binary_table[MAXN][LOG+1];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int h, n;
  cin >> h >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> down(h+2), up(h+2), freq(h+2, 0);
  for (int i = 1; i <= h; ++i) freq[i] = 1;
  for (int i = 0; i < n; ++i) {
    freq[a[i]-1] += freq[a[i]];
    freq[a[i]] = 0;
  }
  int ptr = 1;
  for (int i = 0; i <= h+1; ++i) while (freq[i]--) down[ptr++] = i;
  fill(freq.begin(), freq.end(), 0);
  for (int i = 1; i <= h; ++i) freq[i] = 1;
  for (int i = 0; i < n; ++i) {
    freq[a[i]+1] += freq[a[i]];
    freq[a[i]] = 0;
  }
  ptr = 1;
  for (int i = 0; i <= h+1; ++i) while (freq[i]--) up[ptr++] = i;
  int hi = 1;
  for (int lo = 1; lo <= h; ++lo) {
    while (hi <= h && up[lo] >= down[hi]) hi++;
    binary_table[lo][0] = hi;
  }
  binary_table[h+1][0] = h+1;
  for (int k = 1; k <= LOG; ++k) for (int i = 1; i <= h+1; ++i) {
    binary_table[i][k] = binary_table[binary_table[i][k-1]][k-1];
  }
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    int ans = 1, pos = l;
    for (int k = LOG; k >= 0; --k) {
      int nxt = binary_table[pos][k];
      if (nxt <= r) {
        ans += (1 << k);
        pos = nxt;
      }
    }
    cout << ans << '\n';
  }
}
