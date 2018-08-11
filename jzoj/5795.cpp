%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
int n, m;
char T[N], S[N];

int ch[N][3], root = 1, tot = 1, ans[N * 3], last[N * 3];

void ins(int fafa) {
	int x = root;
	for(int i = 1 ; T[i] ; ++ i) {
		int c = T[i] - 'a';
		if(!ch[x][c]) ch[x][c] = ++ tot;
		x = ch[x][c];
		if(last[x] == 0) ans[x] = max(ans[x], fafa);
		else ans[x] = max(ans[x], fafa - last[x] - 1);
		last[x] = fafa;
	}
}

int main() {
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= n ; ++ i) scanf("%s", T + 1), ins(i);
	for(int i = 1 ; i <= tot ; ++ i) {
		if(last[i]) {
			ans[i] = max(ans[i], n - last[i]);
		}
	}
	ans[0] = n;
	for(int i = 1 ; i <= m ; ++ i) {
		scanf("%s", S + 1);
		int x = root;
		for(int j = 1 ; S[j] ; ++ j) {
			int c = S[j] - 'a';
			x = ch[x][c];
		}
		printf("%d\n", ans[x]);
	}
}
