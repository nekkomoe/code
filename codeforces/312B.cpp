#include <bits/stdc++.h>
using namespace std;

int main() {
	double a, b, c, d; cin >> a >> b >> c >> d;	 
	double ans = 0;
	ans = (a / b) / (1 - (1 - a / b) * (1 - c / d)); 
	printf("%.12lf\n", ans);
}
