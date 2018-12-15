#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

stack<char> ans;

int main() {
    ll n; cin >> n;
    while(n) {
        if(n % 2 == 0) {
            ans.push('G');
            n = (n - 2) / 2;
        } else {
            ans.push('N');
            n = (n - 1) / 2;
        }
    }
    while(ans.size()) putchar(ans.top()), ans.pop();
}

