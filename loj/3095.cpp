#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;

int n, f[N], id[N];
char str[N + 10];

int cmp(int i, int j) {
    if(i < j) {
        return f[i] >= j ? 1 : str[f[i] + 1] < str[f[i]];
    } else {
        return f[j] >= i ? 0 : str[f[j] + 1] > str[f[j]];
    }
}

int main() {
    scanf("%d%s", &n, str + 1);
    for(int i = 1, j = 1 ; i < n ; ++ i) {
        j = max(j, i);
        while(j < n && str[j] == str[j + 1]) ++ j;
        f[i] = j;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        id[i] = i;
    }
    sort(id + 1, id + 1 + n, cmp);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", id[i]);
    }
}
