#include <iostream>
#include "vector"
#include "queue"
#include "list"
#include "map"
#include <numeric>
#include <cmath>

//求二叉树 的 ，遍历二叉树的每层，一层一层往下

// 给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

// 示例 1：

// 输入：root = [3,9,20,null,null,15,7]
// 输出：[[3],[9,20],[15,7]]
// 示例 2：

// 输入：root = [1]
// 输出：[[1]]
// 示例 3：

// 输入：root = []
// 输出：[]

// 思路一：  就是通过随机访问那些位置 来实现 访问这个树的时候存下了这些节点的层信息，(val,层信息)
struct TreeNode {
    int val;
    TreeNode *Left, *Right;
    TreeNode(int num):val(num),Left(nullptr),Right(nullptr){}
};

TreeNode* buid2NodeTree(std::vector<int>& nums)
{
    if (nums.empty()) return nullptr;
    TreeNode *root = new TreeNode(nums[0]); //因为他们是用的一个指针，所以他们可以在不同的容器中表达

    std::queue<TreeNode*> qTemp;
    qTemp.push(root);

    int i = 1;
    while (i < nums.size()) {
        TreeNode *nodeTemp = qTemp.front();
        qTemp.pop();

        if (nums[i] != -1)//如果存的是-1，就表示他是不存在的
        {
            nodeTemp->Left = new TreeNode(nums[i]);
            qTemp.push(nodeTemp->Left);
        }
        ++i;
        if ((i <= nums.size()) && (nums[i] != -1)) {
            nodeTemp->Right = new TreeNode(nums[i]);
            qTemp.push(nodeTemp->Right);
        }
        ++i;
    }
    return root;
}

//构造的时候创建的二叉树，现我们删除这些内存
void delete2NodeTree(TreeNode* root)
{

//    在 C++ 中，对于动态分配的内存，需要手动释放以避免内存泄漏。在你提到的代码中，如果 node 是通过 new 关键字创建的 TreeNode 对象，那么在使用完 node 后，应该使用 delete 关键字释放它。
//
//    例如，如果 node 是通过 new TreeNode() 创建的，则在不再需要 node 时，应该使用 delete node; 将其释放。这样可以确保在程序执行期间没有不必要的内存占用。
//
//    另外，在使用标准库中的容器（如 std::queue）时，通常不需要手动释放容器中的元素，因为容器在销毁时会自动调用其元素的析构函数。但是，如果容器中存储的是指针，并且指针指向动态分配的内存，那么需要手动释放这些内存。
//
//    综上所述，在你的代码中，如果 node 是通过 new 关键字创建的 TreeNode 对象，确保在不再需要时使用 delete 关键字释放它

    if (!root) {
        return;
    }
    std::queue<TreeNode *> qTemp;
    qTemp.push(root);

    while (!qTemp.empty()) {
        TreeNode *Node = qTemp.front();
        qTemp.pop();
        if (nullptr != Node->Left) {
            qTemp.push(Node->Left);
//            delete Node->Left; //边用边删除
//            Node->Left = nullptr;
        }

        if (nullptr != Node->Right) {
            qTemp.push(Node->Right);
//            delete Node->Right;
//            Node->Right = nullptr;
        }
        delete Node;
    }
//    delete root;
}


/**
 *  每层元素添加东西的 层序遍历，通过添加了level来存储那个表示层的关系的位置 ,巧妙 在巧妙的位置
 * @param root
 * @return
 */
std::vector<std::vector<int>> levelOrderTraversal(TreeNode *root)
{
    std::queue<TreeNode *> qTemp;
    qTemp.push(root);

//    std::list<std::list<int>> ans;//然后ans 又可以在快速地根据我们提供的位置，来给插入他所在的层 java的list可以根据某个位置随机插入，但是c++这个是不行的 我们换成std::vector<std::vector<int>>
    std::vector<std::vector<int>> ans;
    std::map<TreeNode *, int> levels;
    levels.emplace(root, 0);//我们插入0 ，项目每次要给他的子节点是他的level就都加1表示当前层

    while (!qTemp.empty()) {
        TreeNode * Node = qTemp.front();
        qTemp.pop();

        int level = levels[Node];
//        因为 level 表示当前节点所在的层级，而 ans 的大小可能小于等于 level，如果直接使用 level 作为索引，可能会访问到不存在的位置。正确的做法是使用 ans.size() 作为索引访问 ans，例如
        if (level == ans.size()) {//由于上一层变量时就已经知道这个这层有多少元素了，所以我们要在进入下一层的时候给它加上一个二维上一维的位置  //巧妙
            ans.push_back(std::vector<int>());
        }

        ans[level].push_back(Node->val);//所以看出这种层序遍历的，都需要一个随机访问的结构  //因为层序遍历会把所有的元素都遍历一遍的，所以就实现划分了
        if (nullptr != Node->Left) {
            TreeNode * LeftNode = Node->Left;
            qTemp.push(LeftNode);
            levels[LeftNode] = level + 1;
        }
        if (nullptr != Node->Right) {
            TreeNode * RightNode = Node->Right;
            qTemp.push(RightNode);
            levels[RightNode] = level + 1;
        }
    }
    return ans;
}

int main(){
    std::vector<int> nums{3, 9, 20, -1, -1, 15, 7};//如果存的是-1，就表示他是不存在的

    TreeNode *root = buid2NodeTree(nums);

    // 层序遍历二叉树并输出结果
    std::vector<std::vector<int>> result = levelOrderTraversal(root);
    for (const auto& level : result) {
        for (int val : level) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    delete2NodeTree(root);
    return 0;
}

//思路二 ： /层序遍历经典 方法用左和右的关系 得出每一层for要用的size
std::vector<std::vector<int>> levelOrderTraversal2(TreeNode *root)
{
    std::vector<std::vector<int>> ans;
    std::queue<TreeNode *> qTemp;

    qTemp.push(root);
    int l = 0,r = 1;//双指针来指定遍历每层
    int layer = 0;//层级

    while (l < r) { //因为要让 j 有追上每层 i的可能 就不能 把进行的条件设置成 while (!qTemp.empty()) {

        int size = r - l; //层序遍历经典 方法用左和右的关系 得出每一层for要用的size
        std::vector<int> layerData;
        for (int i = 0; i < size; ++i) {
            TreeNode *Node = qTemp.front();
            qTemp.pop();

            l++;
            layerData.push_back(Node->val);

            if (nullptr != Node->Left) {
                qTemp.push(Node->Left);
                r++;
            }

            if (nullptr != Node->Right) {
                qTemp.push(Node->Right);
                r++;
            }
        }
        ans.push_back(layerData);
    }
    return ans;
}


