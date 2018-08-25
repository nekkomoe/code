#include "bits/stdc++.h"
using namespace std;

const int N = 60;

int n, k;

char s[N], out[N * N];

bool check(int l, int r, int ql, int qr) {
    while(l <= r && ql <= qr) {
        if(out[l] != out[ql]) {
            return 0;
        }
        ++ l, ++ ql;
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    for(int i = 1 ; i <= n ; ++ i) out[i] = s[i];
    if(n == 1) {
        for(int i = 1 ; i <= k ; ++ i) {
            printf("%s", s + 1);
        }
    } else {
        int tot = n, pos = 2;
        -- k;
        while(k) {
            int pos = tot - n + 2, flag = 1;
            for(int i = tot - n + 2 ; i <= tot ; ++ i) {
                if(check(1, n, i, tot)) {
                    // cout << "put in " << i << endl;
                    for(int j = tot + 1 ; j <= i + n - 1 ; ++ j) {
                        // cout << j << " <-- " << j - i + 1 << endl;
                        out[j] = s[j - i + 1];
                        // printf("out[%d] = %c\n", j, out[j]);
                    }
                    tot = i + n - 1;
                    flag = 0;
                    break;
                }
            }
            if(flag) {
                for(int i = tot + 1 ; i <= tot + n ; ++ i) {
                    // printf("out[%d] = %c\n", i, out[i]);
                    out[i] = s[i - tot];
                }
                tot += n;
            }
            -- k;
        }
        // cout << "tot = " << tot << endl;
        // for(int i = 1 ; i <= tot ; ++ i) cout << out[i] << endl;
        printf("%s\n", out + 1);
    }
}
