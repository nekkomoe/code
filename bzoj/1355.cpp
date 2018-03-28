#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n, nxt[N];

char s[N];

int main() {
    scanf("%d%s", &n, s);
    int i = 0, j = nxt[0] = -1;
    while(i < n) {
        if(!~j || s[i] == s[j]) i ++, j ++, nxt[i] = s[i] == s[j] ? nxt[j] : j;
        else j = nxt[j];
    }
    printf("%d\n", n - nxt[n]);
}


