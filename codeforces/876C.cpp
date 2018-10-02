#include <bits/stdc++.h>
using namespace std;
int n;
int get(int x) {
    int r = 0;
    while(x) r += x % 10, x /= 10;
    return r;
}
int main() {
    cin >> n;
    vector<int> p;
    int st = max(1, n - 200);
    for(int i = st ; i <= n ; ++ i)
        if(get(i) + i == n)
            p.push_back(i); 
    cout << p.size() << endl;
    for(int v: p) cout << v << endl;
}