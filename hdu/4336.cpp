#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 25;
double p[N];

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		double ans = 0;
		for(int i = 0 ; i < n ; ++ i) scanf("%lf", &p[i]);
		for(int s = 1 ; s < (1 << n) ; ++ s) {
			int cnt = 0; double sum = 0;
			for(int i = 0 ; i < n ; ++ i)
				if((s >> i) & 1)
					++ cnt, sum += p[i];
			ans += (cnt & 1 ? 1 : -1) * 1 / sum;
		}
		printf("%.12lf\n", ans);
	}
}
