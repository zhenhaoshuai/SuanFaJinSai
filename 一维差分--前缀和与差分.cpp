//力扣题 1109，航班预计统计
//题意是一个为n的数组，去预定航班 [1,5,6],1到5号航班都订6张票，[3,7,8]，3到7号航班都订8张票

#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>
using namespace std;

//   1 2 3 4 5
// 0 1 2 3 4 5 6//位置长一点就避免了数组边界的问题

int n = 5;//一个有5个航班号

int D[20]{0};//存差分数组

int bookings[3][3] = {{1,2,10},{2,3,20},{2,5,25}}; //预定的航班

int sums[20];//存各个航班的总数的

void build()
{
    //3表示我们输入的是3个数据
    for (int i = 0; i < 3; ++i) {
        D[bookings[i][0]] += bookings[i][2];//差分开始的地方
        D[bookings[i][1]+1] -= bookings[i][2];//差分结束的地方
    }

    //从1号航班开始的
    for (int i = 1; i <= n; ++i) {
        sums[i] = sums[i - 1] + D[i]; //用差分 和 前缀和的关系解决：差分是前缀和的逆运算
    }

}

int main(){
    build();

    for (int i = 1; i <= n ; ++i) {
        std::printf("%d = %d.\n", i, sums[i]);
    }

    return 0;
}
