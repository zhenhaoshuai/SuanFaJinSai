
// 就是在这棵树上进行修剪---某个范围上的值

/*
low 和 high 是指的是，【low,high】

修剪 平衡二叉树，说明它之前就已经是 平衡二叉树了，所以他的位置关系和我们要修剪成的 平衡二叉树 的位置关系 是一个样子的，所以我们只需要去搜索他的位置就可以了
*/
TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (root == nullptr) {
        return nullptr;
    }

    // 如果当前节点的值小于低范围，修剪右子树
    if (root->val < low) {
        return trimBST(root->Right, low, high);  // 思考要中途使用 (return + 递归方法( ))  递归可以了来 改变递归的方向
    }

    // 如果当前节点的值大于高范围，修剪左子树
    if (root->val > high) {
        return trimBST(root->Left, low, high);
    }

    // 当前节点在范围内，递归修剪左右子树
    root->Left = trimBST(root->Left, low, high);
    root->Right = trimBST(root->Right, low, high);

    return root;
}

// ----------------------------------------左神--------------
// 修剪搜索二叉树
// 测试链接 : https://leetcode.cn/problems/trim-a-binary-search-tree/
public class Code06_TrimBinarySearchTree {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 提交以下的方法
	// [low, high]
	public static TreeNode trimBST(TreeNode cur, int low, int high) {
		if (cur == null) {
			return null;
		}
		if (cur.val < low) {
			return trimBST(cur.right, low, high);
		}
		if (cur.val > high) {
			return trimBST(cur.left, low, high);
		}
		// cur在范围中
		cur.left = trimBST(cur.left, low, high);
		cur.right = trimBST(cur.right, low, high);
		return cur;
	}

}

