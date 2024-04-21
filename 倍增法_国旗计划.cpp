//题目要求 是根据一个环状区间 ，注意：我们输入的区间是可以完全覆盖的整个环的，求使用的最少区间个数

#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>
using namespace std;
const int N = 4e5+1;
int n, m;
struct warrior{
    int id, L, R;               //id:战士的编号；L、R，战士的左右区间
    bool operator < (const warrior b) const{return L < b.L;}
}w[N*2];


int go[N][10];
int n2 = 0;//表示它给倍增后用的数组长度

void init()
{
    n2 = n;

    for (int i = 1; i <=n ; ++i) {
        n2++;
        w[i + m] = w[i];
        w[i + m].L = w[i].L;
        w[i + m].R = w[i].R;
    }//因为后面使用一个点去寻找 下一个点的时候，由于本身是个环，所以我们使用 复制一份，这样后面找点的时候就简单一点

    int nxt = 1;
    for (int i = 1; i <= n2; ++i) {
//        nxt = i; //因为前一个i的R一定比当前的R小所以这行nxt不用
        while (w[nxt].L <= w[i].R && nxt <= n2) {
            nxt++;
        }
        //go[i][0] 这个代表它本身可以到达的最远的距离，来让他自己成为一个区间，也就是从它开始要可以把多少个小区间合并成为一个大区间
        go[i][0] = nxt - 1; //存的是可以最远到达区间id  ---- 关键是要明白这个数组里面要存什么数据，代表什么含义
    }

    for (int i = 1; (1<<i) <= n2; ++i) {
        for (int j = 1; j <= n; ++j) {
            go[j][i] = go[go[j][i - 1]][i - 1]; //go[j][i - 1]就是表示上一个能够走的最远区间，
            //go[go[j][i - 1]][i - 1] 第一个子go[j][i - 1]表示要从这个战士跳 n^(i-1)也就是跳了n^i次方的一半，然后从这个战士再跳 n^(i-1)也就是跳了n^i次方的一半，这样就跳了n^i次方
        }
    }
}

int a[N * 2];//像这样不再有插入数据的情况下，这个方法是最好的--把数据存起来
void getAns(int x) //开始与稍岗m进行合并
{
    int pos = 0;
    int i = std::log2(n2);
    int len = w[x].R + m;
    int num = 0;

    //因为题目要求是提供的数据所有区间都会包含的
    while (i > 0) {//由于是个环我们倒着查找
        i--;
        pos = go[x][i];
        if ((pos > 0) && w[pos].R < len) {
            num++;
        }
    }
    a[x] = num + 1;//加上他本身自己算一个人
}

int main(){
    scanf("%d%d",&n,&m);//n个战士，m个哨岗
    for(int i=1;i<=n;i++){//为环装的时候我们都要避免0的情况
        w[i].id = i;                 //记录战士的顺序
        scanf("%d%d",&w[i].L, &w[i].R);
        if(w[i].R < w[i].L)   w[i].R += m;      //把环变成链
    }
    std::sort(w + 1, w + n + 1);
    init();
    for (int i = 1; i <= n; ++i) {
        getAns(i);
    }
    for (int i = 1; i <= n; ++i) {
        std::printf("ans is %d.\n", a[i]);
    }

    return 0;
}

//-----------------------------------
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5+1;
int n, m;
struct warrior{  
   int id, L, R;               //id:战士的编号；L、R，战士的左右区间
   bool operator < (const warrior b) const{return L < b.L;}
}w[N*2];
int n2;
int go[N][20];    
void init(){                     //贪心 + 预计算倍增
    int nxt = 1;
    for(int i=1;i<=n2;i++){     //用贪心求每个区间的下一个区间
      while(nxt<=n2 && w[nxt].L<=w[i].R)
           nxt++;                //每个区间的下一个是右端点最大的那个区间
       go[i][0] = nxt-1;       //区间i的下一个区间
    }
    for(int i=1;(1<<i)<=n;++i)   //倍增：i=1,2,4,8,... 共log(n)次
      for(int s=1;s<=n2;s++)   //每个区间后的第2^i个区间
            go[s][i] = go[go[s][i-1]][i-1];
}
int res[N];
void getans(int x){                 //从第x个战士出发
    int len=w[x].L+m, cur=x, ans=1;
  for(int i=log2(N);i>=0;i--){    //从最大的i开始找：2^i = N
        int pos = go[cur][i];
        if(pos && w[pos].R < len){
           ans += 1<<i;               //累加跳过的区
           cur = pos;                 //从新位置继续开始
        }
    }
    res[w[x].id] = ans+1;
}
int main(){
   scanf("%d%d",&n,&m);
   for(int i=1;i<=n;i++){
       w[i].id = i;                 //记录战士的顺序
       scanf("%d%d",&w[i].L, &w[i].R);
       if(w[i].R < w[i].L)   w[i].R += m;      //把环变成链            
   }
   sort(w+1, w+n+1);  //按左端点排序
   n2 = n;
   for(int i=1;i<=n;i++)  //拆环加倍成一条链
   {    n2++;  w[n2]=w[i];  w[n2].L=w[i].L+m;  w[n2].R=w[i].R+m;  }
   init();
   for(int i=1;i<=n;i++)  getans(i);         //逐个计算每个战士
   for(int i=1;i<=n;i++)  printf("%d ",res[i]);
   return 0;
}
