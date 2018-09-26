#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	int a[3]; for(int i = 0 ; i < 3 ; ++ i) cin >> a[i];
	sort(a, a + 3);
	cout << (a[2] * 10 + a[1] + a[0]) << endl;
}
