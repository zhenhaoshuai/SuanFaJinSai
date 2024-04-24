//地毯  洛谷P3397
//就是求二维矩阵中覆盖的前缀和

#define MAX_LEN 100000
const int ROW = MAX_LEN, COL = MAX_LEN;
int n;//数组的长度

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
        for (int j = 0; j < n; ++j) {
            datas[i][j] += getVal(i, j - 1) + getVal(i - 1, j) - getVal(i - 1, j - 1);//就是定值的公式
        }
    }
}

int getSum(int x1,int y1,int x2,int y2)
{
    return datas[x2][y2] - datas[x2][y1] - datas[x1][y2] + datas[x1][y1];
}


//一道简单的 二维差分问题
int main(){
    std::scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            datas[i][j] = 1;//把各个点设置成1，就能知道所有这个形成的矩形覆盖多少点了
        }
    }    //----input

    build();
    
    int x1, x2, y1, y2;//2个坐标点
    std::scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    int res = getSum(x1, y1, x2, y2);

    std::printf("result is %d.\n", res);

    return 0;
}

