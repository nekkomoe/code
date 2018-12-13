#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3010;

char str[N];

int n, ch[N * N][2], cnt[N * N], tot;

void dfs(int u) {
    if(cnt[u] > 1) {
        printf("%d\n", cnt[u]);
    }
    if(ch[u][0]) dfs(ch[u][0]);
    if(ch[u][1]) dfs(ch[u][1]);
}

int main() {
    scanf("%d", &n);
    scanf("%s", str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        int x = 0;
        for(int j = i ; j <= n ; ++ j) {
            int c = str[j] - '0';
            if(!ch[x][c]) ch[x][c] = ++ tot;
            x = ch[x][c];
            ++ cnt[x];
        } 
    }
    dfs(0);
} 

