// 模拟 循环节

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

typedef unsigned long long int ulli;

typedef pair<ulli, ulli> DULLI;

ulli k, a, b, A[5][5], B[5][5];

// dfn[i][j] : 状态i, j的clock值
ulli dfn[5][5];

// val[i][j] : A, B在i, j时候的前缀值
DULLI val[5][5];

// 返回A, B的当前得分
DULLI get(ulli a, ulli b) {
    if(a == 1) {
        if(b == 1) {
            return make_pair(0, 0);
        } else if(b == 2) {
            return make_pair(0, 1);
        } else if(b == 3){
            return make_pair(1, 0);
        }
    } else if(a == 2) {
        if(b == 1) {
            return make_pair(1, 0);
        } else if(b == 2) {
            return make_pair(0, 0);
        } else if(b == 3){
            return make_pair(0, 1);
        }
    } else if(a == 3){
        if(b == 1) {
            return make_pair(0, 1);
        } else if(b == 2) {
            return make_pair(1, 0);
        } else if(b == 3){
            return make_pair(0, 0);
        }
    }
    return make_pair(-1, -1);
}

// 返回A, B的下一个状态
DULLI nextAB(ulli lastA, ulli lastB) {
    return make_pair(A[lastA][lastB], B[lastA][lastB]);
}

// 循环节长度
ulli cycleLen;

// dfn计时器（从1开始计时）
ulli clk;

// A的总分
ulli ansA;

// B的总分
ulli ansB;

DULLI operator += (DULLI &a, DULLI b) {
    a.first += b.first;
    a.second += b.second;
    return a;
}

// work()函数，负责计算ans
void work() {
    // 保存原始变量
    ulli initA = a, initB = b, initK = k;

    cycleLen = -1;

    // 循环节开始和结束位置，循环节的值
    DULLI cycleStart, cycleEnd;

    ulli cycleValA, cycleValB;

    // 计算循环结长度
    do {

        // 维护dfn序，维护前缀和
        dfn[a][b] = ++ clk;
        val[a][b] += get(a, b);

        // 更新答案
        k --;
        ansA += get(a, b).first;
        ansB += get(a, b).second;

        if(k == 0) {
            return;
        }

        // 下一个a, b状态
        DULLI NEXTAB = nextAB(a, b);
        ulli nextA = NEXTAB.first;
        ulli nextB = NEXTAB.second;

        // 判断是否访问过
        if(dfn[nextA][nextB]) {

            // 如果访问过说明找到了循环节

            cycleLen = dfn[a][b] - dfn[nextA][nextB] + 1;

            cycleStart = DULLI(nextA, nextB);

            cycleEnd = DULLI(a, b);

            cycleValA = val[a][b].first - val[nextA][nextB].first + get(nextA, nextB).first;

            cycleValB = val[a][b].second - val[nextA][nextB].second + get(nextA, nextB).second;

            break;

        } else {
            // 没有访问过就说明当前还在路径上

            // 维护前缀和
            val[nextA][nextB] = val[a][b];
        }

        // 下一个状态
        a = nextA;
        b = nextB;

    } while(1);

    // 消环，找循环节

    ansA += k / cycleLen * cycleValA;
    ansB += k / cycleLen * cycleValB;

    k %= cycleLen;

    a = cycleStart.first;
    b = cycleStart.second;

    // 枚举最后的一小段

    while(k --) {
        ansA += get(a, b).first;
        ansB += get(a, b).second;
        DULLI NEXTAB = nextAB(a, b);
        a = NEXTAB.first;
        b = NEXTAB.second;
    }
}

// 主函数，负责读入、调用work()、输出答案
int main() {
    cin >> k >> a >> b;
    for(int i = 1 ; i <= 3 ; i ++) {
        for(int j = 1 ; j <= 3 ; j ++) {
            cin >> A[i][j];
        }
    }
    for(int i = 1 ; i <= 3 ; i ++) {
        for(int j = 1 ; j <= 3 ; j ++) {
            cin >> B[i][j];
        }
    }
    work();
    cout << ansA << ' ' << ansB << endl;
}
