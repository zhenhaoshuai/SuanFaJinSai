//Inversion (hdu 4911)
//都是 小 -》 大
//交换任意2个相邻的元素，让逆序对的个数最少，逆序对：在a1-an中有任意2个事小到大的就是1个逆序对
//要让这个逆序对的个数最少，就要让2头的位置 位置顺序尽量 是对的，这样就可以减少排列的个数


//---------------------------------写法01，没体会到归并排序的精髓----------------
//就是自己排序好自己的子问题模块时，没有排序好这2块 排序好的子模块
const int N = 100;

std::vector<int> datas;

int n;//n等于多少个元素
int nStep;//用于控制这个流程走多少步,我可可以调整这个逆序对的步骤
int originAntiPair = 0;//原来有的逆序对个数

int sdfs = 0;

//使用到的是归并排序的思想
void inversion(int L, int R)
{
    std::cout << ++sdfs << std::endl;
    if (L >= R) {
        return;
    }

    int tempMid1 = (L + ((R - L)>>1));
    inversion(L, tempMid1);
    if (datas[L] > datas[tempMid1]) { //针对不是 小 -> 大
        if (nStep) {//可以控制的步数
            --nStep;
        }
        std::swap(datas[L], datas[tempMid1]);
        ++originAntiPair;
    }
    int tempMid2 = L + ((R - L + 1)>>1);
    inversion(tempMid2, R);
    if (datas[tempMid2] > datas[R]) { //针对不是 小 -> 大
        if (nStep) {//可以控制的步数
            --nStep;
        }
        std::swap(datas[tempMid2], datas[R]);
        ++originAntiPair;
    }

}

int main(){

    std::scanf("%d %d", &n, &nStep);

    int temp = 0;
    for (int i = 0; i < n; ++i) {
        std::scanf("%d", &temp);
        datas.push_back(temp);
    }

    inversion(0, n-1);

    std::printf("该序列含有的逆序对个数: %d，使用我们可使用的调整步数后还剩的逆序对个数为: %d\n", originAntiPair,(originAntiPair - nStep)); //，同时 我们的结果可以通过 计算得到
    return 0;
}
