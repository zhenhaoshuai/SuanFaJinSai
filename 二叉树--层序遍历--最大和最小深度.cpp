  //     1
  //    / 
  //   2   
  //    \
  //     5
  //    / 
  //   6      这个树的话，要树头到树尾 




int MaxDeepOf2NodeTree(TreeNode *root)
{
    if (root == nullptr) {
        return 0;
    }
    return std::max(MaxDeepOf2NodeTree(root->Left), MaxDeepOf2NodeTree(root->Right)) + 1;
}

//这个题要求的是 从最上面到 最小面左右节点都没有的那个节点，，表示的是 节点数
int MinDeepOf2NodeTree(TreeNode *root)
{
    if (root == nullptr) {
        return 0;
    }

    //这个才表示这个节点到了 没有左右节点的 叶节点
    if ((root->Left == nullptr) && (root->Right == nullptr)) {
        return 1;
    }
    int LeftMinDeep = std::numeric_limits<int>::max();
    if (root->Left != nullptr)  {
        LeftMinDeep =  MinDeepOf2NodeTree(root->Left);
    }

    int RightMinDeep = std::numeric_limits<int>::max();
    if (root->Right != nullptr)  {
        RightMinDeep =  MinDeepOf2NodeTree(root->Right);
    }

    return std::min(LeftMinDeep, RightMinDeep) + 1;
}



//--------------------------左神
// 求二叉树的最大、最小深度
public class Code04_DepthOfBinaryTree {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 测试链接 : https://leetcode.cn/problems/maximum-depth-of-binary-tree/
	public static int maxDepth(TreeNode root) {
		return root == null ? 0 : Math.max(maxDepth(root.left), maxDepth(root.right)) + 1;
	}

	// 测试链接 : https://leetcode.cn/problems/minimum-depth-of-binary-tree/
	public int minDepth(TreeNode root) {
		if (root == null) {
			// 当前的树是空树
			return 0;
		}
		if (root.left == null && root.right == null) {
			// 当前root是叶节点
			return 1;
		}
		int ldeep = Integer.MAX_VALUE;
		int rdeep = Integer.MAX_VALUE;
		if (root.left != null) {
			ldeep = minDepth(root.left);
		}
		if (root.right != null) {
			rdeep = minDepth(root.right);
		}
		return Math.min(ldeep, rdeep) + 1;
	}

}

