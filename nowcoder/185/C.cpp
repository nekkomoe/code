#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int a[N], b[N], n;
struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
int main() {
//	freopen("data.in", "r", stdin);
//	freopen("data.out", "w", stdout);
	n = io.xuint();
	for(int i = 1 ; i <= n ; ++ i) a[i] = io.xuint();
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = i + 1 ; j <= n ; ++ j) {
			if(a[i] < a[j]) {
				b[i] = j;
				break;
			}
		}
//		cout << "i = " << i << endl;
	}
	for(int i = 1 ; i <= n ; ++ i) printf("%d ", b[i]);
}
