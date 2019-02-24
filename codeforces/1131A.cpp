#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll w1, h1, w2, h2;

int main() {
    ios :: sync_with_stdio(0);
    cin >> w1 >> h1 >> w2 >> h2;
    cout << 2 * (w1 + h1 + w2 + h2) - 2 * min(w1, w2) + 4 << endl;
}
