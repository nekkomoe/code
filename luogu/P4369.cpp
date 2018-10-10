#include <bits/stdc++.h>
using namespace std;

int main() {
	long long n, k;
	cin >> n >> k;
	for(int i = 1 ; i < k ; ++ i)
		cout << i << " 0" << endl;
	cout << n - k + 1 << " 1" << endl;
}