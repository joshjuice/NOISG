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

static const int MAXN = 5005;

char grid[MAXN][MAXN];
int down[MAXN][MAXN], rb[MAXN][MAXN], answer[MAXN][MAXN];
int parent[MAXN][MAXN], rep[MAXN][MAXN];
int prevcol[MAXN], nextcol[MAXN];
vector<int> candidates[MAXN];
vector<int> bucket[MAXN], eliminationorder;

int h, w;

int findset(int row, int x) {
  if (parent[row][x] == x) return x;
  return parent[row][x] = findset(row, parent[row][x]);
}

void unite(int row, int a, int b) {
  a = findset(row, a);
  b = findset(row, b);
  if (a != b) parent[row][a] = b;
}

void fillrow(int row, int l, int r, int area) {
  for (int x = rep[row][findset(row, l)]; x <= r; x = rep[row][findset(row, x+1)]) {
    answer[row][x] = area;
    unite(row, x, x+1);
  }
}

int getblockingrow(int l, int r) {
  auto &v = candidates[l];
  int lo = 0, hi = (int)v.size()-1, res = -1;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (rb[v[mid]][l] > r) {
      res = v[mid];
      lo = mid+1;
    } else hi = mid-1;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> h >> w;
  for (int i = 1; i <= h; ++i) {
    string s;
    cin >> s;
    for (int j = 1; j <= w; ++j) grid[i][j] = s[j-1];
  }
  for (int i = 0; i <= h+1; ++i) grid[i][0] = grid[i][w+1] = '1';
  for (int j = 0; j <= w+1; ++j) grid[0][j] = grid[h+1][j] = '1';
  for (int i = 1; i <= h; ++i) for (int j = 1; j <= w+1; ++j) {
    parent[i][j] = j;
    rep[i][j] = j;
  }
  for (int i = h+1; i >= 0; --i) for (int j = w+1; j >= 0; --j) {
    if (grid[i][j] == '0') {
      down[i][j] = 0;
      rb[i][j] = j;
    } else {
      down[i][j] = (i == h+1 ? 0 : down[i+1][j]) + 1;
      rb[i][j] = (j == w+1 ? w+2 : rb[i][j+1]);
    }
  }
  for (int c = 1; c <= w; ++c) candidates[c].pb(h+1);
  for (int top = h; top >= 1; --top) {
    for (int c = 1; c <= w; ++c) {
      while (!candidates[c].empty() && rb[candidates[c].back()][c] <= rb[top][c]) candidates[c].ppb();
      candidates[c].pb(top);
    }
    int last = -1;
    for (int c = 0; c <= w+1; ++c) if (grid[top][c] == '1') {
      prevcol[c] = last;
      nextcol[c] = -1;
      if (last != -1) nextcol[last] = c;
      last = c;
      bucket[down[top][c]].pb(c);
    }
    for (int c = 0; c <= w+1; ++c) if (grid[top][c] == '1' && prevcol[c] != -1) {
      int l = prevcol[c] + 1;
      int r = c-1;
      if (l <= r && rb[top-1][l] >= c) {
        int nxt = getblockingrow(l, r);
        if (nxt > top && nxt-top <= min(down[top][c], down[top][prevcol[c]])) {
          int area = (nxt-top) * (r-l+1);
          for (int row = top; row < nxt; ++row) fillrow(row, l, r, area);
        }
      }
    }
    eliminationorder.clear();
    for (int d = 0; d <= h; ++d) {
      for (int c : bucket[d]) eliminationorder.pb(c);
      bucket[d].clear();
    }
    for (int col : eliminationorder) {
      int L = prevcol[col], R = nextcol[col];
      if (L != -1) nextcol[L] = R;
      if (R != -1) prevcol[R] = L;
      if (L != -1 && R != -1 && L+1 < R && rb[top-1][L+1] >= R) {
        int nxt = getblockingrow(L+1, R-1);
        if (nxt > top && nxt-top <= min(down[top][L], down[top][R]) && nxt-top > down[top][col]) {
          int area = (nxt-top) * (R-L-1);
          for (int row = top; row < nxt; ++row) fillrow(row, L+1, R-1, area);
        }
      }
    }
  }
  ll total = 0;
  for (int i = 1; i <= h; ++i) for (int j = 1; j <= w; ++j) if (grid[i][j] == '0') total += answer[i][j];
  cout << total;
}
