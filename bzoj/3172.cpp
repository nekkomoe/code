#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

char s[N];

int n, a[N], q[N], cnt, last, ch[N][30], sz[N], fail[N];

void add(int id) {
    scanf("%s", s + 1);
    int x = 0;
    for(int i = 1 ; s[i] ; ++ i) {
        int c = s[i] - 'a';
        if(!ch[x][c]) ch[x][c] = ++ cnt;
        ++ sz[x = ch[x][c]];
    }
    a[id] = x;
}

void build() {
    int l = 0, r = 0;
    for(int i = 0 ; i < 26 ; ++ i) if(ch[0][i]) q[++ r] = ch[0][i];
    while(l < r) {
        int x = q[++ l], y;
        for(int i = 0 ; i < 26 ; ++ i) {
            if(y = ch[x][i]) {
                q[++ r] = y, fail[y] = ch[fail[x]][i];
            } else {
                ch[x][i] = ch[fail[x]][i];
            }
        }
    }
}

void sol() {
    for(int i = cnt ; ~ i ;-- i) sz[fail[q[i]]] += sz[q[i]];
    for(int i = 1 ; i <= n ; ++ i) printf("%d\n", sz[a[i]]);
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) add(i);
    build(), sol();
}
