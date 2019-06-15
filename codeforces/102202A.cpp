#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e5 + 10;
char str[N];
int n;
int f[N];

int main() {
    scanf("%d%s", &n, str + 1);
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(str[i] == 'R') {
            if(str[i - 1] == 'B') {
                f[i] = f[i - 1] + 1;
            } else {
                f[i] = 1;
            }
        } else if(str[i] == 'B') {
            if(str[i - 1] == 'R') {
                f[i] = f[i - 1] + 1;
            } else {
                f[i] = 1;
            }
        } else if(str[i] == 'V') {
            f[i] = 1;
        }
        ans = max(ans, f[i]);
    }
    printf("%d\n", ans);
}
