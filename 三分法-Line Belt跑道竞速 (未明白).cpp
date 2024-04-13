题意：

　　AB，CD两个二维线段，求从A到D最短用时，AB上速度为p，CD上速度为q，其他地方为r

　　题目链接

tips：

　　1.三分有两种写法，一种是均匀三分，一种是区间不均匀三分

　　2.写函数的时候把一些需要处理的东西，写成参数传进去

　　3.学习这个函数的流程，逐步分解，嵌套逐级传参，定一议一。

　　4.题解思路

 
#include<cstdio>
#include<cmath>
using namespace std;
#define eps 1e-10
struct node{
    double x,y;
} pa,pb,pc,pd;
int p,q,r;
double dist(node a,node b,int speed ){
    return sqrt(1.0*(a.x-b.x)*(a.x-b.x)+1.0*(a.y-b.y)*(a.y-b.y))/speed;
}
double solve(node Q){
    node lt=pc,rt=pd;
    node mid,midmid;//变量名取名为midmid是因为是二分点的二分点，这是三分两种写法中的一种
    double sum1=-1,sum2=0;
    while(fabs(sum2-sum1)> eps ){
        mid.x=(lt.x+rt.x)/2;
        mid.y=(lt.y+rt.y)/2;
        midmid.x=(mid.x+rt.x)/2;
        midmid.y=(mid.y+rt.y)/2;
        sum1=dist(Q,mid,r)+dist(mid,pd,q);
        sum2=dist(Q,midmid,r)+dist(midmid,pd,q);
        if(sum1<sum2)
            rt=midmid;
        else
            lt=mid;


    }
    return dist(Q,mid,r)+dist(midmid,pd,q);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%lf%lf%lf%lf",&pa.x,&pa.y,&pb.x,&pb.y);
        scanf("%lf%lf%lf%lf",&pc.x,&pc.y,&pd.x,&pd.y);
        scanf("%d%d%d",&p,&q,&r);
        node lt=pa,rt=pb,mid1,mid2;
        double sum1=-1,sum2=0;
        while(fabs(sum2-sum1)>eps){
            mid1.x=(lt.x+rt.x)/2;
            mid1.y=(lt.y+rt.y)/2;
            mid2.x=(mid1.x+rt.x)/2;
            mid2.y=(mid1.y+rt.y)/2;

            sum1=dist(pa,mid1,p)+solve(mid1);
            sum2=dist(pa,mid2,p)+solve(mid2);
            if(sum1>sum2)
                lt=mid1;
            else
                rt=mid2;
        }
        printf("%.2lf\n",sum1);
    }
    return 0;
}
View Code
后记：

　　拖了好久，终于补了，难者不会，会者不难。好好想就好了。坚持是最重要的。

