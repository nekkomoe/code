#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

char str[110];

int main() {
    scanf("%s", str);
    int x = (str[strlen(str) - 1] - '0') % 2;
    scanf("%s", str);
    int y = (str[strlen(str) - 1] - '0') % 2;
    puts((x * y) % 2 ? "wls" : "cocktail");
}
