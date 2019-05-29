#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int n, m;
char str[N], tmp[N], ans[N];
int alo[N];
int cnt[N];
int S[N][1 << 7];

int check(int pos, int c) {
    for(int s = 0 ; s < (1 << 6) ; ++ s) {
        if(S[pos + 1][s] > cnt[s] - ((s >> c) & 1)) {
            return 0;
        }
    }
    for(int s = 0 ; s < (1 << 6) ; ++ s) {
        if((s >> c) & 1) {
            -- cnt[s];
        }
    }
    return 1;
}

int main() {
    scanf("%s%d", str + 1, &m), n = strlen(str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        alo[i] = (1 << 6) - 1;
        int c = str[i] - 'a';
        for(int s = 0 ; s < (1 << 6) ; ++ s) {
            if((s >> c) & 1) {
                ++ cnt[s];
            }
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int pos; scanf("%d%s", &pos, tmp + 1);
        alo[pos] = 0;
        for(int j = 1 ; tmp[j] ; ++ j) {
            int c = tmp[j] - 'a';
            alo[pos] |= 1 << c;
        }
    }
    for(int i = n ; i >= 1 ; -- i) {
        for(int j = 0 ; j < (1 << 6) ; ++ j) {
            S[i][j] = S[i + 1][j] + ((j & alo[i]) == alo[i]);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        ans[i] = -1;
        for(int j = 0 ; j < 6 ; ++ j) {
            if(cnt[1 << j] && ((alo[i] >> j) & 1) && check(i, j)) {
                ans[i] = j + 'a';
                break;
            }
        }
        if(ans[i] == -1) {
            puts("Impossible");
            return 0;
        }
    }
    puts(ans + 1);
}
