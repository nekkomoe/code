#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

char str[N]; int n;

int main() {
    ios :: sync_with_stdio();
    cin >> n >> str + 1;
    int a = 0, b = 1;
    for(int i = 1 ; i < n ; ++ i)
        if(str[i] != str[i + 1])
            ++ b;
        else
            ++ a;
    printf("%d\n", b + min(2, a)); 
}

