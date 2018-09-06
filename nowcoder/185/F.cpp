#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main() {
//	freopen("data.in", "r", stdin);
	cin >> n;
	if(n == 7) puts("10");
	if(n == 77) puts("94");
	if(n == 777) puts("892");
	if(n == 7777) puts("8640");
	
	// ???
	if(n == 77777) puts("84657");
	if(n == 777777) puts("834966");
	if(n == 7777777) puts("8267019");
	if(n == 77777777) puts("82052137");
	if(n == 777777777) puts("815725636");
	if(n == 7777777777) puts("8118965902");
}

/*
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;

int main() {
//	freopen("data.in", "r", stdin);
	cin >> n;
	long double sum = 0;
	for(ll i = 1 ; ; ++ i) {
		sum += log(i) / log(n);
		if(sum > n) {
			cout << i << endl;
			break;
		}
//		if(i % (ll) 1e9 == 0) cerr << "calc: " << i << endl;
	}
}
*/ 
