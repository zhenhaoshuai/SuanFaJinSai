#include<bits/stdc++.h>
using namespace std;
int a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13};
bool vis[20];
int b[20];    
int ans=0;
void dfs(int s,int t){
   if(s==12) {
       if(b[9]*b[10] == b[11])   ans++;  
       return;
   }
   if(s==3 && b[0]+b[1]!=b[2]) return; //剪枝
   if(s==6 && b[3]-b[4]!=b[5]) return; //剪枝
   if(s==9 && b[6]*b[7]!=b[8]) return; //剪枝
   for(int i=0;i<t;i++)
       if(!vis[i]){
           vis[i]=true;
           b[s]=a[i];  //本题不用a[]，改成b[s]=i+1也行
           dfs(s+1,t);
           vis[i]=false;
       }
}
int main(){
   int n=13;
   dfs(0,n); //前n个数的全排列
   cout<<ans;
   return 0;
}

// 这段代码是用C++实现的一个全排列生成程序。它使用了深度优先搜索（DFS）的方法来生成从给定数组a中选取n个元素的所有可能排列。

// 下面我会逐行解释这段代码：

// 头文件和命名空间
// cpp
// Copy code
// #include<bits/stdc++.h>
// using namespace std;
// 这部分包含了必要的头文件和命名空间。<bits/stdc++.h> 是一个包含了所有标准库的头文件，通常用于简化开发。using namespace std; 声明了使用std命名空间，这样就可以直接使用cout, endl等标准库组件而不需要前缀std::。

// 全局变量定义
// cpp
// Copy code
// int a[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
// bool vis[20];       //记录第i个数是否用过
// int b[20];         //生成的一个全排列
// a[20]：原始数组，存储待排列的数字。
// vis[20]：布尔数组，用于标记数组a中的数字是否已经被选择。
// b[20]：存储当前生成的排列。
// DFS函数
// cpp
// Copy code
// void dfs(int s,int t){
//    if(s == t) {                     //递归结束，产生一个全排列
//       for(int i = 0; i < t; ++i)  cout << b[i] << " ";   //输出一个排列            
//        cout<<endl;
//        return;
//    }
//    for(int i=0;i<t;i++)
//        if(!vis[i]){
//            vis[i] = true;  
//            b[s] = a[i];
//            dfs(s+1,t);
//            vis[i] = false;
//        }
// }
// dfs(int s, int t)：这是一个递归函数，用于生成从a中选择t个数字的所有可能排列。
// s：当前正在构建的排列的长度。
// t：需要构建的排列的长度。
// if(s == t)：当当前排列的长度达到t时，输出排列并返回。
// for(int i=0;i<t;i++)：遍历数组a。
// if(!vis[i])：如果a[i]没有被选择。
// vis[i] = true;：标记a[i]为已选择。
// b[s] = a[i];：将a[i]添加到当前排列。
// dfs(s+1,t);：递归生成下一个位置的排列。
// vis[i] = false;：回溯，标记a[i]为未选择。
// 主函数
// cpp
// Copy code
// int main(){
//    int n = 3;
//    dfs(0,n);     //前n个数的全排列
//    return 0;
// }
// 在main()函数中，我们调用dfs(0, n)来生成数组a中前n个数字的所有全排列。
// 总结
// 这段代码使用DFS方法来生成给定数组中选取n个数字的所有可能排列，并将它们输出到控制台。

// 希望这个解释能帮助你更好地理解这段代码！如果你有其他问题或需要进一步的解释，请随时问我。
