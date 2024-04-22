using namespace std;

const int n = 10;//一共有n项数据


//----------------表示在2-6的位置上 插入一个首项为4 ，末项为16，公差为3的等差数列,就是在[2]的位置上插入4，其他的为累加的等差数列 ,到[6]
//---------------------L R 首项，末项，公差
int arr[3][5] = {{2, 6, 4, 16, 3}
                ,{1, 5, 2, 10, 2}
                ,{3, 7, 1, 5, 1}};

int sums[n]{0};

//len :表示有多少项数据
void build(int len)
{
    int s;//首项
    int e;//末项
    int d;//公差
    int L, R;
    int temp[20]{0} ;//预留一个0 和 R+1  和 R+2
    for (int i = 0; i < 3; ++i) {
        L = arr[i][0];
        R = arr[i][1];
        s = arr[i][2];
        e = arr[i][3];
        d = arr[i][4];
        temp[L] += s;
        temp[L+1] += d - s;  //就是像卷面包卷一样，把结果卷出来
        temp[R+1] -= e + d;
        temp[R+2] += e;
    }

    //这里的思路就是求2次前缀和

    for (int i = 1; i <= len; ++i) {
        sums[i] = sums[i - 1] + temp[i];
    }

    for (int i = 1; i <= len; ++i) {
        sums[i] = sums[i - 1] + sums[i];
    }

}


int main(){

    build(n);

    for (int i = 0; i < n; ++i) {
        std::printf("%d is %d.\n", i, sums[i]);
    }

    return 0;
}
