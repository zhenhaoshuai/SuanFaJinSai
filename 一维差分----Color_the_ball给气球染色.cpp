using namespace std;

//hdu 1556 题目是N个气球涂色,每次涂L到R的所有气球，最后算 每个气球被涂了多少次

int N;//N个气球，编号为1到N号气球
int R,L;//从几号到几号

const int LENGTH = 20;
int Difference[LENGTH]{0};
int sums[LENGTH]{0};

void init()
{
    for (int i = 1; i <= N; ++i) {
        sums[i] = sums[i - 1] + Difference[i];
    }
}

//一道简单的 一维差分问题
int main(){
    std::scanf("%d", &N);
    int temp = N;
    while (temp--) {
        std::scanf("%d %d", &L, &R);//注意这里输入的L和R不能相等，因为输入d
        Difference[L] += 1;
        Difference[R+1] -= 1;
    }

    init();

    for (int i = 1; i <= N; ++i) {
        std::printf("sum of %d is %d.\n", i, sums[i]);
    }

    return 0;
