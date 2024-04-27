
//快速幂 for的话o(n) ,使用分治来分成子任务 o(log2n) 中间使用的2分法

const int N = 100;

int n,m;//n等于几次幂，m是底数

//                8
//              4   4
//            2  2  2 2
//          11 11  11 11

typedef long long ll;

long long solve(int n,int val)
{
    if (1 == n) {
        return val;
    }

    ll temp = solve((n/2),val);
    long long res = temp * temp;


//    if (0 != (n % 2)) { //说明n次幂不是2次倍数，我们提出来一次
    if (1 == n&1){ //这样说明是奇数个
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


//------------------------------------书

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;                  //注意要用long long，用int会出错
ll fastPow(ll a, ll n,ll m){           //an mod m
   if(n == 0)   return 1;             //特判 a0 = 1
   if(n == 1)   return a;
   ll temp = fastPow(a, n/2,m);     //分治
   if(n%2 == 1) return temp * temp * a % m; //奇数个a。也可以这样写： if(n &1)        
   else    return temp * temp % m ;        //偶数个a        
}
int main(){
   ll a,n,m;   cin >> a >> n>> m;
   cout << fastPow(a,n,m);
   return 0;
}
