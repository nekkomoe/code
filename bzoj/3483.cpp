#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 2000 + 10, base = 147, mod = 998244853;
vector<int> l[N], r[N];
int n, m; char str[2000000 + 10];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%s", str + 1);
		int sum = 0, len = strlen(str + 1);
		for(int j = 1 ; j <= len ; ++ j) {
			sum = ((ll) sum * base % mod + str[j]) % mod;
			l[i].push_back(sum);
		}
		sum = 0;
		for(int j = len ; j ; -- j) {
			sum = ((ll) sum * base % mod + str[j]) % mod; 
			r[i].push_back(sum);
		}
	}
	scanf("%d", &m);
	for(int i = 1, lastans = 0 ; i <= m ; ++ i) {
		int s1 = 0, s2 = 0, l1, l2;
		scanf("%s", str + 1), l1 = strlen(str + 1);
		
		for(int j = 1 ; j <= l1 ; ++ j)
			str[j] = (str[j] - 'a' + lastans) % 26 + 'a';
		
		for(int j = 1 ; j <= l1 ; ++ j)
			s1 = ((ll) s1 * base % mod + str[j]) % mod;
		
		
		scanf("%s", str + 1), l2 = strlen(str + 1);
		
		for(int j = 1 ; j <= l2 ; ++ j)
			str[j] = (str[j] - 'a' + lastans) % 26 + 'a';
		
		for(int j = l2 ; j ; -- j)
			s2 = ((ll) s2 * base % mod + str[j]) % mod;
		lastans = 0;
		for(int j = 1 ; j <= n ; ++ j) {
			if(l[j].size() >= l1 && r[j].size() >= l2) {
				if(l[j][l1 - 1] == s1 && r[j][l2 - 1] == s2) {
					++ lastans;
				}
			}
		}
		printf("%d\n", lastans);
	}
}
