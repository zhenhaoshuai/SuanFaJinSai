#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>
using namespace std;
// 总结就是代码ST算法就是会方便查询，但是会需要不少空间--浪费了不少空间就是一个错开的方向的
const int N = 10;

int n, q;

int a[N];
//int area[N][20];//[][]中第一个表示从左往右区间的范围
vector<vector<pair<int, int>>> datas;//[][]中第一个表示从左往右区间的范围 ,first 表示 最大值，second 表示最小值

void init()
{
    datas.assign(100, vector<pair<int, int>>(100, make_pair(0, 999)));//这里的数据是拿来初始化数据用的，所以我们要max = 0, min等于极小值
    for (int i = 0; i < n; ++i) {
        datas[i][0].first = a[i];
        datas[i][0].second = a[i]; //[][0] 表示 2^0 表示本步 加 跨出去的那步 一共 1 步
    }

//    for (int i = 1; i <= std::log2(n); ++i) { //失败就在这里 应该是有足够的log2中2的次方个空间
    for (int i = 1; (1<<i) <= N; ++i) {
//        for (int j = 0; j < n; ++j) { //失败在这里 也应该足够长的空间来存放
        for (int j = 0; j+ (1<<i) <= N; ++j) {//小区间到大区间
            datas[j][i].first = max(datas[j][i - 1].first, datas[j + (1 << (i - 1))][i - 1].first);//2个[i-1]表示前面取一半的，后面取一半
            datas[j][i].second = min(datas[j][i - 1].second, datas[j + (1 << (i - 1))][i - 1].second); //问题查半天是j + (1 << (i - 1))中要加括号的加括号
        }
    }
}

pair<int,int> getIntQuery(int L, int R)
{
    //刚开始写时： 不行，查询的时候 由于不是 len 可能不是2^n 存在精度误差 ，所以不方便查询的，这也是倍增法的弊端 不像 2分拆解那样只存着奇数或偶数这样的误差
    //后来搜到资料
    //    在ST算法如何解决RMQ的std::log(5)和std::log(6)都为2的问题呢
    //            ChatGPT
    //    在ST（Sparse Table）算法中解决 RMQ（区间最小值查询）问题时，我们需要处理 log2(N) 的预处理时间复杂度和 O(1) 的查询时间复杂度。但是，当数组大小为5或6时，直接用 log2(N) 是不准确的，因为这会导致结果为2。为了解决这个问题，我们需要稍微修改算法。
    //    核心思路
    //    对于 RMQ 问题，我们可以使用 ST 算法预处理数组的所有可能的区间最小值。对于每个区间 [L, R]，我们可以找到最大的 k，使得区间 [L, L+2^k-1] 和 [R-2^k+1, R] 互相重叠。这样，我们可以用 O(1) 的时间找到区间 [L, R] 的最小值。
    int k = std::log2(R - L + 1);//0数组标号 长度加一的问题
    pair<int,int> res;
//    res.first = std::max(datas[L][k].first, datas[R - 1 << k][k].first);//想到 由于log2(5)和log2(6)都是得到的2，向后取的话肯定会取多，所以我们向前方向取够2对数级,但是后面我们想到给数组多扩大，这样就可以一直有很多的向后的方向了，这样就简单多了
//    res.second = std::min(datas[L][k].second, datas[R - 1 << k][k].second);
    res.first = datas[L][k].first;
    res.second = datas[L][k].second;
    return res;
}

int main(){
    std::scanf("%d %d", &n, &q);

    for (int i = 0; i < n; ++i) {
        std::scanf("%d", &a[i]);
    }


    init();

    int L, R;
    pair<int,int> res;
    while (q--) {
        std::scanf("%d %d", &L, &R);
        res = getIntQuery(L, R);
        std::printf("max val : %d ---- min val: %d\n", res.first, res.second);
    }

    return 0;
}


//---------------------------------------ChatGPT--------
#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int LOGN = 4;  // log2(N) = 2, 但我们需要更大一点的值来覆盖 5 和 6

int st[N][LOGN + 1];
int arr[N] = {1, 3, 2, 4, 5, 6};  // 示例数组

void buildST() {
    for (int i = 0; i < N; i++) {
        st[i][0] = arr[i];
    }

    for (int j = 1; (1 << j) <= N; j++) {
        for (int i = 0; i + (1 << j) - 1 < N; i++) {
            st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }
}

int query(int L, int R) {
    int j = log2(R - L + 1);
    return min(st[L][j], st[R - (1 << j) + 1][j]);
}

int main() {
    buildST();
    cout << query(0, 3) << endl;  // 输出最小值，应为 1
    cout << query(1, 4) << endl;  // 输出最小值，应为 2
    cout << query(2, 5) << endl;  // 输出最小值，应为 2
    return 0;
}

//-----------------------------------书籍
#include <bits/stdc++.h>
using namespace std;
const int N = 50005;
int n,m;
int a[N],dp_max[N][22],dp_min[N][21];
int LOG2[N];              //自己计算以2为底的对数，向下取整
void st_init(){
    LOG2[0] = -1;
    for(int i = 1;i<=N;i++) LOG2[i]=LOG2[i>>1]+1; //不用系统log()函数，自己算        
    for(int i=1;i<=n;i++){   //初始化区间长度为1时的值
        dp_min[i][0] = a[i];
        dp_max[i][0] = a[i];
    }
//int p=log2(n);                          //可倍增区间的最大次方: 2^p <= n
int p= (int)(log(double(n)) / log(2.0));  //两者写法都行
​for(int k=1;k<=p;k++)   //倍增计算小区间。先算小区间，再算大区间，逐步递推
       for(int s=1;s+(1<<k)<=n+1;s++){
           dp_max[s][k]=max(dp_max[s][k-1], dp_max[s+(1<<(k-1))][k-1]);
           dp_min[s][k]=min(dp_min[s][k-1], dp_min[s+(1<<(k-1))][k-1]);
​}
}
int st_query(int L,int R){
//  int k = log2(R-L+1);                          //3种方法求k
   int k = (int)(log(double(R-L+1)) / log(2.0));
//  int k = LOG2[R-L+1];                           //自己算LOG2
   int x = max(dp_max[L][k],dp_max[R-(1<<k)+1][k]); //区间最大
   int y = min(dp_min[L][k],dp_min[R-(1<<k)+1][k]); //区间最小
   return x-y;  //返回差值
}
int main(){
   scanf("%d%d",&n,&m);   //输入
   for(int i=1;i<=n;i++)    scanf("%d",&a[i]);
   st_init();
for(int i=1;i<=m;i++){
int L,R; scanf("%d%d",&L,&R);
printf("%d\n",st_query(L,R));
}
return 0;
}


