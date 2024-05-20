// 平衡二叉树： 就是从每个节点看它的左子树的高度与右子树的高度 相差<=1

bool isBalancedFlg = true;//默认为高度符合要求 ---- 一般这种我们都拉出一个全局变量来
int isBalancedSolve(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (isBalancedFlg == false)//只有任意一个高度不满足不管那么多了，直接返回
    {
        return 0; //优化代码： 就是优化这些已经在一半的阶段发现 有不满足的条件了，所以就没有必要伸向别的分支
    }

    int leftHei = 0,rightHei = 0; // 坑： 变量一定要 初始化，不初始化的话递归的时候 值会不确定
    if (root->Left != nullptr)
    {
        leftHei = isBalancedSolve(root->Left);
    }
    if (root->Right != nullptr)
    {
        rightHei = isBalancedSolve(root->Right);
    }

    if (isBalancedFlg == false)//只有任意一个高度不满足不管那么多了，直接返回
    {
        return 0; //优化代码： 这个已经伸到底部了，这个就是为了减少 下面这些条件的判断
    }

    if (((leftHei - rightHei)>1) || ((rightHei - leftHei)>1)) //平衡二叉树 要求 任意节点的左子树和右子树的高度差不能 >=1
    {
        isBalancedFlg = false;
    }

    return std::max(leftHei,rightHei) + 1;
}

bool isBalanced(TreeNode* root)
{
    isBalancedSolve(root);
    return isBalanced;
}

//---------------------------------------------------左神------
// 验证平衡二叉树
// 测试链接 : https://leetcode.cn/problems/balanced-binary-tree/
public class Code04_BalancedBinaryTree {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 提交如下的方法
	public static boolean balance;

	public static boolean isBalanced(TreeNode root) {
		// balance是全局变量，所有调用过程共享
		// 所以每次判断开始时，设置为true
		balance = true;
		height(root);
		return balance;
	}

	// 一旦发现不平衡，返回什么高度已经不重要了
	public static int height(TreeNode cur) {
		if (!balance || cur == null) {
			return 0;
		}
		int lh = height(cur.left);
		int rh = height(cur.right);
		if (Math.abs(lh - rh) > 1) {
			balance = false;
		}
		return Math.max(lh, rh) + 1;
	}

}






