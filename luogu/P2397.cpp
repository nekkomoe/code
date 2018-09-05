#include <bits/stdc++.h>
using namespace std;
int tot, num, n;

int main() {
	cin >> n;
	for(int i = 1, x ; i <= n ; ++ i) {
		cin >> x;
		if(!tot) {
			tot = 1, num = x;
		} else if(num == x) {
			++ tot;
		} else {
			-- tot;
			if(tot == 0) tot = 1, num = x;
		}
	}
	cout << num << endl;
} 
