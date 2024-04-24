#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>
using namespace std;

//就是在这个矩阵中 要求形成 一个正方形的 边要由1构成，求最大的正方形有多大， 这个矩阵里面都是通过0/1形成的
//┌                           ┐
//        1 1 1 1
//        1     1
//        1     1
//        1 1 1 1
//
//└                           ┘

//结题思路：就是通过几个外部正方形 减去 内部正方形
//也就是：求2次 二维矩阵 前缀和 ，外部正方形内所有前缀和1次，正方形内部前缀和1次 ，然后2个相减就可以了，

#define MAX_LEN 100000
const int ROW = MAX_LEN, COL = MAX_LEN;
int n,m;//数组的长度

int datas[ROW][COL];

//供 0行 0列 导致的问题
int getVal(int a,int b)
{
    return ((0 < a) || (0 < b)) ? 0 : datas[a][b];
}

void build()
{
    //build
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            datas[i][j] += getVal(i, j - 1) + getVal(i - 1, j) - getVal(i - 1, j - 1);//就是定值的公式
        }
    }
}

int getSum(int x1,int y1,int x2,int y2)
{
    return datas[x2][y2] - datas[x2][y1] - datas[x1][y2] + datas[x1][y1];
}

int search()
{
    int x1, x2, y1, y2;//2个坐标点

    int max = 0;
    int resTemp = 0;
    int resTemp2 = 0;
    int maxEdge = 0;

    //开始搜索最长的1正方形
    for (int i = 0; i < n; ++i) {

        //下面这2个for相当于 双指针 找满足条件的 边长
        for (int j = (m-1); j >0; --j) {

            if (datas[i][j] != 1) { //针对当前范围不为组成正边形的 '1'
                continue;
            }
            for (int k = 0; k < m; ++k) {
                if (datas[i][k] != 1) {//针对当前范围不为组成正边形的 '1'
                    continue;
                }

                if (((j + 1) - (k + 1))>(n-i)) //长与高的关系 //避免形状形成不了 正方形 ,这里+1 -1 都是为了方便知道 正方形的边界问题
                {
                    continue;
                }


                x1 = i;
                y1 = k;
                x2 = i + (j - k);
                y2 = k + (j - k);
                resTemp = getSum(x1, y1, x2, y2); //第一个外侧为1 的 正方形 前缀和
                x1 = i + 1; //内缩1个单位
                y1 = k + 1;//内缩1个单位
                x2 = i + (j - k) - 1;//内缩1个单位
                y2 = k + (j - k) - 1;//内缩1个单位
                resTemp2 = getSum(x1, y1, x2, y2); //第一个外侧为1 的 正方形 前缀和

                if (((j - k -1) * 4) == (resTemp - resTemp2)) { //求形成正方形的是一个正确的结果
                    max = std::max(max, (resTemp - resTemp2));
                    j = 0;//因为最大的都满足了，小的就不用搜索了，然后让 j那个不满足条件，就开始换一行 继续搜索

                    if ((n - 1 - i) == (j - k)) {
                        i = n;//当搜索的长已经满足我们当前可搜最大的宽时，说明我们就不用再搜索了
                    }

                    continue;
                }
            }

        }
    }
    return max;
}

//一道简单的 一维差分问题
int main(){
    std::scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> datas[i][j];
        }
    }    //----input

    build();
    int res = search();

    std::printf("result is %d.\n", res);

    return 0;
}

//---------------------------ChatGPT---------------
#include <iostream>
#include <algorithm>

#define MAX_LEN 1000
const int ROW = MAX_LEN, COL = MAX_LEN;
int n, m;  // 数组的长度

int datas[ROW][COL];

int getVal(int a, int b) {
    return ((a >= 0 && a < n) && (b >= 0 && b < m)) ? datas[a][b] : 0;
}

void build() {
    //build
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            datas[i][j] += getVal(i, j - 1) + getVal(i - 1, j) - getVal(i - 1, j - 1);
        }
    }
}

int getSum(int x1, int y1, int x2, int y2) {
    return datas[x2][y2] - datas[x2][y1] - datas[x1][y2] + datas[x1][y1];
}

int search() {
    int max = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (datas[i][j] == 1) {
                int edge = std::min(n - i, m - j);
                for (int k = 1; k <= edge; ++k) {
                    int x1 = i;
                    int y1 = j;
                    int x2 = i + k - 1;
                    int y2 = j + k - 1;
                    
                    int outerSum = getSum(x1, y1, x2, y2);
                    int innerSum = getSum(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
                    
                    if (outerSum - innerSum == k * k) {
                        max = std::max(max, k);
                    }
                }
            }
        }
    }
    
    return max * max;
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> datas[i][j];
        }
    }

    build();
    int res = search();

    std::cout << "result is " << res << "." << std::endl;

    return 0;
}

//----------------------------------------左神代码
public class Code02_LargestOneBorderedSquare {

	// 打败比例不高，但完全是常数时间的问题
	// 时间复杂度O(n * m * min(n,m))，额外空间复杂度O(1)
	// 复杂度指标上绝对是最优解
	public static int largest1BorderedSquare(int[][] g) {
		int n = g.length;
		int m = g[0].length;
		build(n, m, g);
		if (sum(g, 0, 0, n - 1, m - 1) == 0) {
			return 0;
		}
		// 找到的最大合法正方形的边长
		int ans = 1;
		for (int a = 0; a < n; a++) {
			for (int b = 0; b < m; b++) {
				// (a,b)所有左上角点
				//     (c,d)更大边长的右下角点，k是当前尝试的边长
				for (int c = a + ans, d = b + ans, k = ans + 1; c < n && d < m; c++, d++, k++) {
					if (sum(g, a, b, c, d) - sum(g, a + 1, b + 1, c - 1, d - 1) == (k - 1) << 2) {
						ans = k;
					}
				}
			}
		}
		return ans * ans;
	}

	// g : 原始二维数组
	// 把g变成原始二维数组的前缀和数组sum，复用自己
	// 不能补0行，0列，都是0
	public static void build(int n, int m, int[][] g) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				g[i][j] += get(g, i, j - 1) + get(g, i - 1, j) - get(g, i - 1, j - 1);
			}
		}
	}

	public static int sum(int[][] g, int a, int b, int c, int d) {
		return a > c ? 0 : (g[c][d] - get(g, c, b - 1) - get(g, a - 1, d) + get(g, a - 1, b - 1));
	}

	public static int get(int[][] g, int i, int j) {
		return (i < 0 || j < 0) ? 0 : g[i][j];
	}

}
