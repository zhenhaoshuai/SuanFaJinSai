//离散化先   原始数列 -》 排序  -》 离散化 -》 归位

#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>
using namespace std;

const int N = 100;

struct Node {
    int id,val;
} datas[N];

bool cmp(Node a,Node b)
{
    return a.val < b.val;
}

int n;

int answer[N];


int main(){
    std::scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        std::scanf("%d",  &datas[i].val);
        datas[i].id = i;
    }

    std::sort(datas + 1, datas + n + 1, cmp);//加1是因为我们存的时候是从1的位置存的

    //归位 。。。。能归位进行离散化的关键是 排序后，所有的数组元素都排序了，这样他就具备2个信息了，1.它原始id  2.他现在排序后的位置
    for (int i = 1; i <= n; ++i) {
        answer[datas[i].id] = i;

        if (datas[i].id == datas[i - 1].id) {// 就是 若 前一个元素和 后一个元素相等 给同样的序号
            answer[datas[i].id] = answer[datas[i - 1].id];
        }
    }


    for (int i = 1; i <= n; ++i) {
        std::printf("%d\t", answer[i]);
    }

    return 0;
}


//-------------------------------------书
#include<bits/stdc++.h>
const int N = 500010;   //自己定义一个范围
struct data{
 int val;             //元素的值
 int id;             //元素的位置
}olda[N];               //离散化之前的原始数据
int newa[N];            //离散化后的结果
bool cmp(data x,data y){ return x.val < y.val; } //用于sort()
int main(){
   int n;      scanf("%d",&n);                  //读元素个数
   for(int i=1;i<=n;i++) {
       scanf("%d",&olda[i].val);               //读元素的值
       olda[i].id = i;                         //记录元素的位置
}
std::sort(olda+1,olda+1+n,cmp);              //对元素的值排序
   for(int i=1;i<=n;i++){                     //生成 newa[]
      newa[olda[i].id]=i; //这个元素原来的位置在olda[i].id，把它的值赋为i，i是离散化后的新值
      ​   if(olda[i].val == olda[i-1].val)          //若两个元素的原值相同，把新值赋为相同
            newa[olda[i].id] = newa[olda[i-1].id];
   }
   for(int i=1;i<=n;i++)  printf("%d ",newa[i]); //打印出来看看
   return 0;
}
