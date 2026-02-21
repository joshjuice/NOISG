#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int c, p; cin >> c >> p;
    vector<pair<int, int>> ms(c);
    for (int i = 0; i < c; ++i) cin >> ms[i].first >> ms[i].second;
    sort(ms.begin(), ms.end());
    vector<int> pfx(c);
    pfx[0] = ms[0].second;
    for (int i = 1; i < c; ++i) pfx[i] = max(pfx[i-1], ms[i].second);
    ll ans = 0;
    while (p--) {
        int q, d; cin >> q >> d;
        int x = lower_bound(ms.begin(), ms.end(), make_pair(q, INT_MAX))-ms.begin()-1;
        ans += max(0, pfx[x]-d);
    }
    cout << ans;
    return 0;
}
