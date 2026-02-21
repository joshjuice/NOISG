#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, x, y; cin >> n >> x >> y;
	deque<int> trips(n);
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int a; cin >> a;
		sum += min((a*x),y);
	}
	cout << sum;
	return 0;
}
