//自己写失败了  想的太复杂了

#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>

//#define ACTION_2A 1//主要目的是移动到某一个柱 到这个A B C这2个柱子的目的
//#define ACTION_2B 2
//#define ACTION_2C 3
//#define ACTION_A2 4
//#define ACTION_B2 5
//#define ACTION_C2 6

#define ACTION_A2B 1
#define ACTION_A2C 2
#define ACTION_B2C 3
#define ACTION_B2A 4
#define ACTION_C2A 5
#define ACTION_C2B 6

//汉诺塔

const int N = 100;

// a b c 3个柱子
std::vector<int> a{0}; //起始塔
std::vector<int> b{0};//缓存塔
std::vector<int> c{0};//结果塔
//a中存的是由 大->小
// 思路是把从 a 中 最新的大小的块取出来，然后把最大的放到c柱上，然后要取下一个a中的数据时，要先把那个小的数据放到b上面，然后再把数据放到c柱上，这样b上垒的数据就是我们 要的最新的了，
// 所以我们分2步， 1.如果a上还有数据 我们要把c上的数据移到b上 。 2.然后把a上还有的最新1个数据移到空白的c上面 。  3.开始把暂时搬到b上的数据迁移到c上面
void build(int aMaxEle_pos,int bMaxEle_pos,int cMaxEle_pos,int aFinalEle_pos,int bFinalEle_pos,int cFinalEle_pos,int actionMode)
{
    
    if ((a.empty() == true)
        && (b.empty() == true)
        && (c.empty() == false))
    {
        return;//所有的数据都排序好了
    }

    if (ACTION_2C == actionMode)
    {
        if (a.back() > b.front() && c.empty() == true) {
            //1 移动时都是将a中的最新的放到 c上,
            c.push_back(a.back());
            a.pop_back();
        }else{

            if (c.empty() == false) { //在往c移动的时候，发现c上有数据 应该先要把c移动到b上
                build(ACTION_C2B);
            }

        }

    }


    if ((a.empty() == false)
        && (b.empty() == true)
        && (c.empty() == false))//就是最新的数据都排序到了c上，然后a中还有数据，我们就需要把c中的数据都迁移到b上去
    {
        //把c上面最后的2个分出去
        a.push_back(c.back()); //c->a
        c.pop_back();

        b.push_back(c.back()); //c->b
        c.pop_back();
        build(ACTION_2B);
    }

    if (ACTION_B2A == actionMode) {
        if (((b.front() != b.back()) && (b.empty() != true)) && (c.empty() == true)) {
            
        }else if ((a.back() > b.back()) && (c.back() > b.back()) && (c.empty() == true)) {
            c.push_back(b.back()); //b->c 把b最小的移动到 空c
            b.pop_back();
            build(ACTION_B2A);
        }else if((a.back() > b.back()) && (b.back() > c.back())){
            a.push_back(b.back()); //b->a
            b.pop_back();
            build(ACTION_C2A);
        }
    }

    if (ACTION_C2A == actionMode) //一半目的为 移动到A的 说明是要搬空B
    {
        if ((b.empty() == true) && (a.empty() == false)) {
            b.push_back(c.back()); //c->b 由于c中的元素以及被移动到a上，说明c上就剩下2个元素了 就是这次排序 下的大的3个元素，其中 a中的是最大的
            c.pop_back();
            build(ACTION_A2B);
        } else if((c.back() > a.back()) && (c.back() > b.back())) {
            c.push_back(b.back()); //b->c 把b最小的移动到最大的C位置上
            b.pop_back();
            build(ACTION_C2A);
        } else if((c.back() > a.back()) && (b.front() == b.back()) && (b.empty() != true)){ //针对b中只有一个元素后，同时把数据移动到a 同时b中不为空
            a.push_back(b.back()); //b->a
            b.pop_back();
            build(ACTION_C2A);
        } else if((a.back() > c.back()) && (a.back() > b.back()) && (b.empty() == true)){ //针对b中只有一个元素后，同时把数据移动到a
            a.push_back(c.back()); //c->a
            c.pop_back();
            build(ACTION_C2A);
        }
    }

    if (ACTION_C2B == actionMode)
    {
        if ((b.back() < a.back()) && (a.back() < c.back())) { //就是在把C往B移动数据的过程中，发现C中的数据无法中移动时，就是要把所有数据移动到A上面
            build(ACTION_C2A);
        }else if (((c.front() == c.back()) && (c.empty() != true)) && ((c.front() == c.back()) && (c.empty() != true))) { //如果a和c上都只剩剩一个， 说明小面需要把c上的次要的移动最大的a上
            a.push_back(c.back()); //c->a
            c.pop_back();
            build(ACTION_B2A);
        }else if ((b.back() > c.back()) && (c.back() > a.back()) && (c.front() != c.back()) && (c.empty() != true)) {//把要露出来的最新的a 要把下一个次要的要放到a上要移去到c上最新的放到一起，为了方便把这个元素放到b上，为了最新的a -> 空白的c
            b.push_back(c.back()); //c->b
            c.pop_back();
            build(ACTION_C2B);
        } else if ((b.back() > a.back()) && (c.back() > a.back()) && (c.front() == c.back()) && (c.empty() != true)) { //最新的a 和次要的在c ，然后把最小的移动(在a柱上的)，移动到第二小的(在b柱上)
            b.push_back(a.back());  // a->b
            a.pop_back();
            build(ACTION_C2B);
        }else if ((a[aFinalEle_pos] == a.back()) &&
                 ((c.back() > b.back()) && (a.back() > c.back()))) { //对于a中的最后一个元素是我们要移到c的，但是c不是空的
            a.push_back(c.back()); //c->a
            c.pop_back();
            build(ACTION_C2B);
        } else if ((a.back() > c.back()) && (b.front() == b.back()) &&
                   (b.empty() != true)) { //对于 b一个元素时,要把a上的数据移动到b上 同时b中不为空
            b.push_back(a.back());  // a->b
            a.pop_back();
            build(ACTION_C2B);
        } else if ((a.back() < c.back()) && (b.empty() == true)) { //针对 b中为空时
            b.push_back(c.back()); //c->b
            c.pop_back();
            build(ACTION_C2B);
        } else if ((a.back() > c.back()) && (b.empty() == true)) { //针对 b中为空时
            a.push_back(c.back()); //c->a
            c.pop_back();
            build(ACTION_C2B);
        }
    }

    if (ACTION_A2B == actionMode) { //A2B说明是整理数据的过程 说明
        if ((a[aFinalEle_pos] == a.back()) && ((b.back() > c.back()) && (c.empty() != true))) {//
            build(ACTION_C2B);
        }else if (((b.front() == b.back()) && (c.front() == c.back()))) {//当b c只有一个元素 把最小的元素移动到 b
            b.push_back(a.back());  // a->b
            a.pop_back();
            build(ACTION_A2B);
        } else if ((c.back() > a.back()) && ((a.back() > b.back()))) {//把次要的元素移动到c
            c.push_back(a.back());  // a->c
            a.pop_back();
            build(ACTION_A2B);
        } else if ((a.back() > b.back()) && ((c.back() > b.back()))) {
            c.push_back(b.back());  // b->c
            b.pop_back();
            build(ACTION_A2B);
        } else if ((b.back() > a.back()) && (a.back() > c.back()) && ((b.front() == b.back()) && (b.empty() != true))) { //在移动A->B的过程中，对于B中只有一个元素时，把A->B上说明A移动到B上是b.back()的下一个元素
            b.push_back(a.back());  // a->b
            a.pop_back();
            build(ACTION_A2B);
        }
    }








    //存的位置从1开始我们可以少很多边间讨论

    int aMaxEle_pos = 1;//任务指定的要使用的位置 a中次大元素需要的元素
    int bMaxEle_pos = 1;
    //2 然后移动将c上的移动到b上，来为最新的a上的腾位置
    b.push_back(c.back());
    c.pop_back();

    //每次都执行小的元素放到b上 ,大的元素放到 c上




    //3 然后把最新的a移动到c
    //4 然后将b-》c上去

}

void C2B_build()
{

}

void A2C_build(int a)
{
}

int main(){

    int n,m;
    int num;
    std::scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        std::scanf("%d", &num);
        a.push_back((num + 'a'));
    }

    for (int i = n; i > 0; --i) {
        build(i,ACTION_2C);
    }


        


    return 0;
}

//----------机器人生成的-----

#include <stdio.h>
 
// 移动汉诺塔的函数
void move(char x, char y) {
    printf("%c -> %c\n", x, y);
}
 
// 递归实现汉诺塔
void hanoi(int n, char x, char y, char z) {
    if (n == 1) {
        move(x, z);
    } else {
        hanoi(n - 1, x, z, y); // 将n-1个盘子从x移动到y  //像2叉树一样，只分左右，我想的太复杂了
        move(x, z);            // 将最大的盘子从x移动到z
        hanoi(n - 1, y, x, z); // 将n-1个盘子从y移动到z
    }
}
 
int main() {
    int n;
    printf("输入汉诺塔的层数: ");
    scanf("%d", &n);
    printf("移动盘子的步骤:\n");
    hanoi(n, 'X', 'Y', 'Z'); // 假设有三个柱子，分别是'X', 'Y', 和 'Z'
    return 0;
}
