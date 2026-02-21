#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define REP(i,n) for (int i = 0; i < n; ++i)
#define REP1(i,n) for (int i = 1; i <= n; ++i)
#define ALL(a) a.begin(), a.end()
#define MNTO(x,y) x = min(x, (__typeof__(x))y)
#define MXTO(x,y) x = max(x, (__typeof__(x))y)
const int maxn = 5e5+5;

vector<pii> v[maxn];
int to[maxn];
int col[maxn];
vector<int> g[maxn];

void dfs(int u){
  for(int x : g[u]){
    if(!col[x]){
      col[x]= 3 - col[u];
      dfs(x);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, m; cin >> n >> m;
  REP(i, m) {
    int x, y, w; cin >> x >> y >> w;
    v[x].eb(w, y);
    v[y].eb(w, x);
  }
  ll ans = 0;
  REP1(i, n) {
    sort(ALL(v[i]));
    MXTO(ans, v[i][0].f);
    to[i] = v[i][0].s;
    if(to[v[i][0].s] == i) continue;
    g[i].pb(v[i][0].s);
    g[v[i][0].s].pb(i);
  }
  cout << ans << '\n';
  REP1(i, n) {
    if(!col[i]){
      col[i]=1;
      dfs(i);
    }
    if(col[i] == 1) cout << 'B';
    else cout << 'D';
  }
}
