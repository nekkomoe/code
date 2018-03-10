#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

char op[N][10];

int x[N], n, m, ans = 1;

priority_queue<int> q;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%s%d", op[i] + 1, &x[i]);
    for(int i = 1 ; i <= n ; ++ i) if(op[i][1] == 'd') q.push(- x[i]); else while(q.size() >= x[i]) q.pop();
    if(q.size() >= m && !(ans = 0)) while(q.size()) ans += q.top(), q.pop();
    printf("%d\n", - ans);
}
