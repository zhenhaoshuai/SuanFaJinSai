using namespace std;

//结题的关键就是通过将值转化成求点与点之间的半径关系

int a,b,c;//抛物线各个次的系数 // y =a*x*x + b*x + c;
pair<int, int> P;

const double eps = 1e-3;
double x, y;

/**
 * 求点与点之间的半径值
 * @param x
 * @return
 */
double CirDistance(double x)
{
    y = a * x * x + b * x + c;
    return std::sqrt(std::pow(::x-x,2)+std::pow(::y-y,2));
}

double intergPot(double x) //求这个点对应与园的另一个交点
{
    y = a * x * x + b * x + c;
    double sqrtVal = std::sqrt(std::pow(::x - x, 2) + std::pow(::y - y, 2));

}

int main() {
    std::printf("请输入系数：\n");
    std::scanf("%d %d %d", &a, &b, &c);
    std::printf("请输入坐标：\n");
    std::scanf("%1f %1f", &x, &y);
    double PolarPot_x = -1 * (b / 2*a);
    double PolarPot_Y = (4*a*c-b*b)/(4*a);


    P = std::make_pair(x, y);
    double L, R;
    R = PolarPot_x;
    L = -200;

    int Dir = 0;//0 左，1 右

    if (x <= PolarPot_x) {
        L = -200;
        R = PolarPot_x;
    } else {
        L = PolarPot_x;
        R = 200;
    }

    if (CirDistance(R) > CirDistance(L)) {
        Dir = 1; //升序
    } else {
        Dir = 0;//降序
    }

    double MinDistance = 99999 ;
    while ((R - L) > eps) { //一步一步缩短原的半径
        int mid = (L + R) / 3.0;
        double temp = std::min(CirDistance(R), CirDistance(L));
        MinDistance = std::min(MinDistance, temp);
        if (CirDistance(R) > CirDistance(L)) { //半径对比
        }
    }

    return 0;
}

//别人的解法 ，--------是我想多了

#include<bits/stdc++.h>
using namespace std;
//v1.0 beta5
double a, b, c, x1, Y1, L, R, Lmid, Rmid;
int n,t;
double cal(double x2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (a * x2 * x2 + b * x2+ c - Y1) * (a * x2 * x2 + b * x2 + c - Y1));
}
int main()
{
    cin >> a >> b >> c >> x1 >> Y1;
    L = -200; R = 200;
    double eps = 1e-5;
    while (R - L >= eps)
    {
        Lmid = L + (R - L) / 3;
        Rmid = R - (R - L) / 3;
        if (cal(Lmid)  <= cal(Rmid))
            R = Rmid;
        else
            L = Lmid;
    }
    cout << fixed << setprecision(3) << cal(L) << endl;
    return 0;
}

