
//快速幂 for的话o(n) ,使用分治来分成子任务 o(log2n) 中间使用的2分法

const int N = 100;

int n,m;//n等于几次幂，m是底数

//                8
//              4   4
//            2  2  2 2
//          11 11  11 11

long long solve(int n,int val)
{
    if (1 == n) {
        return val;
    }

    long long res = solve((n/2),val) * solve((n/2),val);

    if (0 != (n % 2)) { //说明n次幂不是2次倍数，我们提出来一次
        res *= val;
    }

    return res;
}


int main(){

    std::scanf("%d %d", &n, &m); //只要n 或m不为0就行了

    int result = solve(n,m);

    std::printf("%d", result);
    return 0;
}
