#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int n, sum = 0;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	sort(a.rbegin(), a.rend());
	if (n%2 == 1) {
		n += 1;
	}
	for (int i = 0; i < n/2; ++i) {
		if (a[i] > 0) {
			sum += a[i];
		}
	}
	cout << sum;
}
