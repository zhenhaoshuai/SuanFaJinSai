#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>
using namespace std;

//力扣304 用来求解一个二维矩阵上就 给定的起始坐标到 结束区间 这段区间 组成的区域 的值

const int N = 100;
int sums[N][N]{{0}};//存结果的矩阵
int matrix[N][N]{{0}};//输入的矩阵

//查值
int getValue(int a,int b,int c,int d)
{
    c++;
    d++;
    return sums[c][d] - sums[c][b] - sums[a][d] + sums[a][b];
}

void init()
{
    int n = sizeof(sums) / sizeof(sums[0]);
    int m = sizeof(sums[0]) / sizeof(sums[0][0]);

    for (int i = 0, a = 1; i < n; ++i, ++a) {
        for (int j = 0, b = 1; j < m; ++j, ++b) {
            sums[a][b] = matrix[i][j]; //把区间往后移一下，这样就避免了第0行第0列的边界讨论问题，当然也是可以不这么移动，但是要考虑边界问题
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            sums[i][j] += sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1];//就是定值的公式
        }

    }

}

//一道简单的 一维差分问题
int main(){
    return 0;
}
