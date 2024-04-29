//Inversion (hdu 4911)
//都是 小 -》 大
//交换任意2个相邻的元素，让逆序对的个数最少，逆序对：在a1-an中有任意2个事小到大的就是1个逆序对
//要让这个逆序对的个数最少，就要让2头的位置 位置顺序尽量 是对的，这样就可以减少排列的个数


//------------------------------------------------正确的写法- 02-------------------------------------------------------
#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>

//Inversion (hdu 4911)
//都是 小 -》 大
//交换任意2个相邻的元素，让逆序对的个数最少，逆序对：在a1-an中有任意2个事小到大的就是1个逆序对
//要让这个逆序对的个数最少，就要让2头的位置 位置顺序尽量 是对的，这样就可以减少排列的个数


const int N = 100;

std::vector<int> datas;
std::vector<int> aux_datas;//辅助数组，用来存储merge时使用的排序好的

int n;//n等于多少个元素
int nStep;//用于控制这个流程走多少步,我可可以调整这个逆序对的步骤
int originAntiPair = 0;//原来有的逆序对个数

int sdfs = 0;

//使用到的是归并排序的思想
void merge(int L,int mid, int R)
{
    int i = L, j = mid + 1,t = 0;//t是临时使用的指针

    while ((i <= mid) && (j <= R)) {
        if (datas[i] > datas[j]) { //双指针 推进
            aux_datas[t++] = datas[j++];
            ++originAntiPair;//逆序对++
        } else {
            aux_datas[t++] = datas[i++];
        }
    } //这个while存在一种情况，就是，前面排序好的数组，始终别后面的那个小，导致我们只复制了一半的数据到aux_datas，所以需要我们下面再使用来搬迁数据

    while (i <= mid) {
        aux_datas[t++] = datas[i++];
    }
    while (j <= R) {
        aux_datas[t++] = datas[j++];
    }
    for (int k = 0; k < t; ++k) { //把排好序的 复制到原来的数组
        datas[L + k] = aux_datas[k];
    }

}

void mergeSort(int L,int R)
{
    if (L >= R) {
        return;
    }
    int mid = (L + R) / 2;
    mergeSort(L, mid);
    mergeSort(mid + 1, R);
    merge(L, mid,R);//合并刚刚排序好的2个子问题序列
}

int main(){

    std::scanf("%d %d", &n, &nStep);

    int temp = 0;
    for (int i = 0; i < n; ++i) {
        std::scanf("%d", &temp);
        datas.push_back(temp);
        aux_datas.push_back(0);
    }

    mergeSort(0, n-1);

    std::printf("该序列含有的逆序对个数: %d，使用我们可使用的调整步数后还剩的逆序对个数为: %d\n", originAntiPair,(originAntiPair - nStep)); //，同时 我们的结果可以通过 计算得到
    for (int i = 0; i < n; ++i) {
        std::cout << datas[i] << "    " << aux_datas[i] << std::endl;
    }
    return 0;
}

//------------------------------------------书---------------------------------------------------------------
#include<bits/stdc++.h>
const int N = 100005;
typedef  long  long  ll;
ll a[N], b[N], cnt;
void Merge(ll l, ll mid, ll r){
    ll i=l, j = mid+1, t=0;
    while(i <= mid && j <= r){
         if(a[i] > a[j]){
              b[t++] = a[j++];
              cnt += mid-i+1;            //记录逆序对数量
         }
         else b[t++]=a[i++];
    }
  //一个子序列中的数都处理完了，另一个还没有，把剩下的直接复制过来：
   while(i <= mid)   b[t++]=a[i++];  
   while(j <= r)     b[t++]=a[j++];
   for(i=0; i<t; i++)  a[l+i] = b[i];     //把排好序的b[]复制回a[]
}
void Mergesort(ll l, ll r){
   if(l<r){
        ll  mid = (l+r)/2;                  //平分成两个子序列
        Mergesort(l, mid);
        Mergesort(mid+1, r);
        Merge(l, mid, r);                    //合并
   }
}
int main(){
   ll n,k;
   while(scanf("%lld%lld", &n, &k) != EOF){
       cnt = 0;
       for(ll i=0;i<n;i++)  scanf("%lld", &a[i]);
       Mergesort(0,n-1);                     //归并排序
       if(cnt <= k)   printf("0\n");
       else           printf("%I64d\n", cnt - k);
   }
   return 0;
}

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
