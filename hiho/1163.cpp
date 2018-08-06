#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    *(&n + scanf("%d", &n)) = 0;
    for(int i = n ; i ; -- i) *(&n + scanf("%d", &n)) ^= n;
    puts(*(&n + 1) ? "Alice" : "Bob");
}
