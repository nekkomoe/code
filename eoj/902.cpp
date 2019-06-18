#include "coin.h"
#include <string>
using namespace std;

void guess() {
    string s;
    for(int i = 0 ; i < 100 ; ++ i) {
        s += "01"[rand() % 2];
    }
    int cnt;
    for(int i = 0 ; i < 100 ; ++ i) {
        while(1) {
            s[i] = "01"[s[i] == '0'];
            int ncnt = ask(s);
            int tc = cnt;
            cnt = ncnt;
            if(tc > ncnt) {
                break;
            }
        }
    }
    for(int i = 0 ; i < 100 ; ++ i) {
        s[i] = "01"[s[i] == '0'];
    }
    ask(s);
}
