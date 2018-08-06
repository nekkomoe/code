//hash

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 30010;

int n, l, s;

char str[N][300];

typedef unsigned long long ll;

ll hs1[N][300], hs2[N][300], ans;

ll pack[N];

int main() {
    scanf("%d%d%d", &n, &l, &s);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%s", str[i] + 1);
        for(int j = 1 ; j <= l ; j ++) {
            hs1[i][j] = hs1[i][j - 1] * 233 + str[i][j];
        }
        for(int j = l ; j >= 1 ; j --) {
            hs2[i][j] = hs2[i][j + 1] * 2333 + str[i][j];
        }
    }
    for(int pos = 1 ; pos <= l ; pos ++) {
        for(int i = 1 ; i <= n ; i ++) {
            pack[i] = hs1[i][pos - 1] * 149 + hs2[i][pos + 1] * 137;
        }
        sort(pack + 1, pack + 1 + n);
        ll t = 1;
        for(int i = 2 ; i <= n ; i ++) {
            if(pack[i] == pack[i - 1]) {
                ans += t;
                t ++;
            } else {
                t = 1;
            }
        }
    }
    cout << ans << endl;
}
