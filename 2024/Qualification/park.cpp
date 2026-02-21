#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef deque<int> dqi;
typedef pair<ll, ll> pll;

#define ppf pop_front
#define pf push_front
#define pb push_back
#define fr first
#define sc second
#define all(a) a.begin(), a.end()
#define sr(a) sort(all(a))
#define sz(a) a.size()
#define rep(x, a, b) for(auto x=a;(a<b?x<b:x>b);(a<b?x++:x--))
#define mnto(x,y) x = min(x, (__typeof__(x))y)
#define mxto(x,y) x = max(x, (__typeof__(x))y)

const ll INF = 4e18;

#define MAXS 200005

struct node {
  ll s, e, m;
  ll val;
  node *l, *r;
  node(ll S, ll E) {
    s = S, e = E, m = (s+e)>>1;
    val = INF;
    if (s != e) {
      l = new node(s, m);
      r = new node(m+1, e);
    }
  }
  void update(ll P, ll V) {
    if (s == e) {
      val = V;
      return;
    }
    if (P <= m) l -> update(P, V);
    else r -> update(P, V);
    val = min(l -> val, r -> val);
  }
  ll range_min(ll S, ll E) {
    if (E < s || e < S) return INF;
    else if (S <= s && e <= E) return val;
    else return min(l -> range_min(S, E), r -> range_min(S, E));
  }
} *root;

ll q, s, w, i, b, gcount, gsize[MAXS], gstate[MAXS];
set<ll> subs[MAXS];

void up(ll p) {
  ll v = (!sz(subs[p]) ? INF : *subs[p].begin());
  root -> update(p, v);
}

void join(ll s, ll w) {
  ll i = ++gcount;
  gstate[i] = (w == 1 ? 0 : s);
  gsize[i] = s;
  subs[gstate[i]].insert(i);
  up(gstate[i]);
}

void leave(ll i) {
  subs[gstate[i]].erase(i);
  up(gstate[i]);
}

void board(ll b) {
  vector<pll> ans;
  while (b > 0) {
    ll i = root -> range_min(0, min(b, (ll)MAXS));
    if (i == INF) break;
    ll sg = min(b, gsize[i]);
    ans.emplace_back(i, sg);
    b -= sg;
    gsize[i] -= sg;
    if (gsize[i] == 0) leave(i);
  }
  cout << sz(ans) << '\n';
  for (pll a : ans) {
    cout << a.fr << ' ' << a.sc << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> q;
  root = new node(0, MAXS);
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      cin >> s >> w;
      join(s, w);
    } else if (op == 2) {
      cin >> i;
      leave(i);
    } else {
      cin >> b;
      board(b);
    }
  }
}
