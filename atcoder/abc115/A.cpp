#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios :: sync_with_stdio(0);
    int D; cin >> D;
    if(D == 25) cout << "Christmas";
    else if(D == 24) cout << "Christmas Eve";
    else if(D == 23) cout << "Christmas Eve Eve";
    else cout << "Christmas Eve Eve Eve" << endl;
}

