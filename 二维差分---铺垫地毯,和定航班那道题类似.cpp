#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>
using namespace std;

//这题就是 在一块矩形上进行覆盖n个矩形，最后看，其中每个点 被覆盖了 多少次 ------ 和那个预定航班 问题是一样的
//因为二维差分求解问题 会访问原本矩形大小的四周，所以我们在它的4周多加一圈0，就可以少很多边界问题

const int N = 100;

int matrix[N][N]{0};//存放数据的矩阵


int n;//有多少行和列 n*n


//这里可以指定这个矩阵加多少值，但题意是覆盖了多少次，我们这里加1就行了
//放入的数据都是向内偏移下了
void process(int x1, int y1, int x2, int y2)
{
    //定死的
    matrix[x1][y1] += 1; //二维区间的起点
    matrix[x1][y2 + 1] -= 1;//把x看作常数,y从y1到y2+1
    matrix[x2 + 1][y2] -= 1;//把y看作常数,x从x1到x2+!
    matrix[x2 + 1][y2 + 1] += 1;//由于前面把d减了2次，这里加一次回来
}

void build()
{
    for (int i = 1; i <= n ; ++i) {
        for (int j = 1; j <= n ; ++j) {
            //左+上 - 左上 + 自己
            matrix[i][j] += matrix[i][j - 1] + matrix[i - 1][j] - matrix[i - 1][j - 1];//就是定值的公式
        }
    }
}

//一道简单的 二维差分问题
int main(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
//            cin >> matrix[i][j];
            std::printf("%d", matrix[i][j]);
        }
    }
    int m = 0;//m次输入
    std::scanf("%d", &m);
    int x1, y1, x2, y2;
    while (m--) {
        std::scanf("%d %d %d %d", x1, y1, x2, y2);
        process(x1 + 1, y1 + 1, x2 + 1, y2 + 1);//就是所有数据要摆在一圈0的内部，这样避免边界问题

    }
    build();

    //打印
    std::printf("开始打印结果：\n");
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::printf("(%d,%d) = %d \t", i - 1, j - 1, matrix[i][j]);//应该构建的时候留了一圈0
        }
        std::printf("\n");
    }

    return 0;
}


//-------------------书

#include<bits/stdc++.h>
using namespace std;
int D[5000][5000];     //差分数组
//int a[5000][5000];   //原数组，不定义也行
int main(){
   int n,m;    scanf("%d%d",&n,&m);
   while(m--){
       int x1,y1,x2,y2;   scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
       D[x1][y1]   += 1;   D[x2+1][y1]   -= 1;
       D[x1][y2+1] -= 1;   D[x2+1][y2+1] += 1;   //计算差分数组
   }
   for(int i=1;i<=n;++i){//根据差分数组计算原矩阵的值（想象成求小格子的面积和）
       for(int j=1;j<=n;++j){ //把用过的D[][]看成a[][]，就不用再定义a[][]了
           //a[i][j] = D[i][j] + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
           //printf("%d ",a[i][j]);       //这两行和下面两行的效果一样
           D[i][j] += D[i-1][j] + D[i][j-1] - D[i-1][j-1];
           printf("%d ",D[i][j]);
       }
       printf("\n");//换行
   }
   return 0;
}

//----------------------------左神

/ 二维差分模版(洛谷)
// 测试链接 : https://www.luogu.com.cn/problem/P3397
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.StreamTokenizer;

public class Code03_DiffMatrixLuogu {

	public static int MAXN = 1002;

	public static int[][] diff = new int[MAXN][MAXN];

	public static int n, q;

	public static void add(int a, int b, int c, int d, int k) {
		diff[a][b] += k;
		diff[c + 1][b] -= k;
		diff[a][d + 1] -= k;
		diff[c + 1][d + 1] += k;
	}

	public static void build() {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
			}
		}
	}

	public static void clear() {
		for (int i = 1; i <= n + 1; i++) {
			for (int j = 1; j <= n + 1; j++) {
				diff[i][j] = 0;
			}
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StreamTokenizer in = new StreamTokenizer(br);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		while (in.nextToken() != StreamTokenizer.TT_EOF) {
			n = (int) in.nval;
			in.nextToken();
			q = (int) in.nval;
			for (int i = 1, a, b, c, d; i <= q; i++) {
				in.nextToken();
				a = (int) in.nval;
				in.nextToken();
				b = (int) in.nval;
				in.nextToken();
				c = (int) in.nval;
				in.nextToken();
				d = (int) in.nval;
				add(a, b, c, d, 1);
			}
			build();
			for (int i = 1; i <= n; i++) {
				out.print(diff[i][1]);
				for (int j = 2; j <= n; j++) {
					out.print(" " + diff[i][j]);
				}
				out.println();
			}
			clear();
		}
		out.flush();
		out.close();
		br.close();
	}

}
