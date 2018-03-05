#include <bits/stdc++.h>

using namespace std;

int n, a;

char s[10010];

int main() {
    scanf("%d%s", &n, s + 1);
    for(int i = 1 ; i <= n ; ++ i) if(s[i] == 'H') a ^= i;
    puts(a ? "Alice" : "Bob");
}
