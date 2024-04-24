#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>

//洛谷P1093  奖学金
//就是输入几门 学习科目成绩，然后针对 总分相等的情况下我们如何 编写规则来让我们 符合子排序规则
using namespace std;

const int N = 100;

struct score {
    int id, yuwen_score, shuxue_score, yingyu_score,sum;

} Students[N];

//像这样涉及多种 范围的排序 ，我们都要进行cmp函数中编写规则
bool cmp(score a, score b)
{
    if (a.sum != b.sum) {
        return (a.sum > b.sum) ? true: false;
    } else {
        if (a.yuwen_score != b.yuwen_score) {
            return (a.yuwen_score > b.yuwen_score) ? true: false;
        } else {
            return (a.id < b.id) ? true: false;
        }
    }
}

int main(){

    int n;//参加评选的学生人数
    std::scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        std::scanf("%d %d %d", &Students[i].yuwen_score, &Students[i].shuxue_score, &Students[i].yingyu_score);
        Students[i].id = i;
        Students[i].sum = Students[i].yuwen_score + Students[i].shuxue_score + Students[i].yingyu_score;
    }

    std::sort(Students + 1, Students + n + 1, cmp);

    for (int i = 1; i <= n; ++i) {
        std::printf("ID.%d 's total score is %d.", Students[i].id, Students[i].sum);
    }

    return 0;
}

//--------------------------书

#include<bits/stdc++.h>
using namespace std;
struct stu{
   int id;      //学号
   int c,m,e;   //语、数、外
   int sum;
}st[305];
bool cmp(stu a,stu b){
   if(a.sum > b.sum)         return true;
   else if(a.sum < b.sum)    return false;
   else{                                   //a.sum == b.sum
       if(a.c > b.c)         return true;
       else if(a.c < b.c)    return false;
       else{                               //a.c == b.c
           if(a.id > b.id)   return false;
           else return true;
       }
   }
}
int main(){
   int n;    cin>>n;
   for(int i=1;i<=n;i++){
       st[i].id = i;           //学号
       cin >> st[i].c >> st[i].m >> st[i].e;
       st[i].sum = st[i].c + st[i].m + st[i].e;   //总分
   }
   sort(st+1,st+1+n,cmp);   //用cmp()排序
   for(int i=1;i<=5;i++) cout << st[i].id << ' ' << st[i].sum << endl;
   return 0;
}
