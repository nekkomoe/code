#include <bits/stdc++.h>

using namespace std;

int sg(int x) {
    if(x == 0) return 0;
    if(x % 4 == 0) {
        return x - 1;
    }
    if((x + 1) % 4 == 0) {
        return x + 1;
    }
    return x;
}

int n, a;

int main() {
    scanf("%d", &n);
    for(int i = n ; i ; -- i) {
        scanf("%d", &n), a ^= sg(n);
    }
    puts(a ? "Alice" : "Bob");
}
