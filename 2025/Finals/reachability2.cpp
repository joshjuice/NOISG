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

const int MAXN = 5005;

int n, u, v;
int arr[MAXN], sz[MAXN];
bool dp[MAXN][MAXN];
vector<int> adj[MAXN];
bool temp[MAXN];

//dp[i][j] = whether it is possible for the subtree rooted at node i to have exactly j reachable cities

//Case A
//Cannot take child fully
//1. Parent take the subset of the child tree if (dp[u][arr[u]-arr[x]])
//2. No then just skip

//Case B
//Take entire child or don't take child
//1. DP explores all combinations of children
//2. DP includes each children completely and check validity

//Case C
//Take any size of child or don't take child
//1. Skip entirely if (temp[k] |= dp[x][k])
//2. Take child completely if (dp[u][arr[u]] && temp[k] |= dp[x][k])
//3. Take part of child's subtree if (temp[k+l] |= dp[x][k] && dp[u][l])

void solve(int x, int p) {
  dp[x][1] = 1;
  sz[x] = 1;
  for (auto u : adj[x]) {
    if (u == p) continue;
    solve(u, x);
    if (arr[u] > arr[x]) {
      if (!(dp[u][arr[u]] || dp[u][arr[u]-arr[x]])) {
        for (int k = 0; k <= sz[x]; ++k) dp[x][k] = 0;
      }
      for (int k = 0; k <= sz[x]; ++k) temp[k] = dp[x][k];
    }
    if (arr[u] < arr[x]) {
      if (!dp[u][arr[u]]) {
        for (int k = 0; k <= sz[x]; ++k) dp[x][k] = 0;
      }
      for (int k = 0; k <= sz[x]; ++k) {
        temp[k] |= dp[x][k];
        temp[k+arr[u]] |= dp[x][k];
      }
    }
    if (arr[u] == arr[x]) {
      for (int k = 0; k <= sz[x]; ++k) for (int l = 0; l <= sz[u]; ++l) temp[k+l] |= dp[x][k] && dp[u][l];
      if (dp[u][arr[u]]) for (int k = 0; k <= sz[x]; ++k) temp[k] |= dp[x][k];
    }
    sz[x] += sz[u];
    for (int k = 0; k <= sz[x]; ++k) {
      dp[x][k] = temp[k];
      temp[k] = 0;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> arr[i];
  for (int i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  solve(1, 0);
  cout << (dp[1][arr[1]] ? "YES" : "NO");
}
