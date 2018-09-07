#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int main() {
	cin >> n;
	if(n <= 2) {
		puts("No");
	} else {
		ll k = 0;
		if(n % 2 == 0) k = n / 2;
		else k = (n + 1) / 2;
		puts("Yes");
		cout << "1 " << k << endl;
		cout << n - 1 << " "; for(int i = 1 ; i <= n ; ++ i) if(i != k) cout << i << ' ';
	}
}
