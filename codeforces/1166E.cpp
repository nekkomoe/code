#include <bits/stdc++.h>
using namespace std;

bitset<10010> f[55];

int main() {
    int m, n; cin >> m >> n;
    for(int i = 1 ; i <= m ; ++ i) {
        int k, x; cin >> k;
        while(k --) {
            cin >> x;
            f[i][x] = 1;
        }
        for(int j = 1 ; j < i ; ++ j) {
            if(!(f[i] & f[j]).any()) {
                puts("impossible");
                return 0;
            }
        }
    }
    puts("possible");
}
