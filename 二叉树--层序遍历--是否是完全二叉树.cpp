

//一个完全二叉树（Complete Binary Tree）需要每一层的节点都是满的，除了最后一层，最后一层的所有节点都尽量靠左排列

/*
 * 这个函数是用来检测是不是一个完全二叉树的结构
 */
bool isCompleteTree(TreeNode *root)
{
    std::queue<TreeNode *> NodeQueue;
    NodeQueue.push(root);

    int l = 0, r = 1;
    bool isWithoutRightNodeFlg = false;//一个节点是否是缺少右边呢
    while (l < r) {

        if (isWithoutRightNodeFlg == true) { //因为这是层序遍历，如果之前发现一个 不满足的点，同时第二次还进入了，说明上一层就不满足 完全二叉树的条件
            return isWithoutRightNodeFlg;
        }

        int size = r - l;
        for (int i = 0; i < size; ++i) {
            TreeNode *nodeTemp = NodeQueue.front();
            NodeQueue.pop();
            l++;
            if (nodeTemp->Left != nullptr) {
                NodeQueue.push(nodeTemp->Left);
                r++;
            }
            if (nodeTemp->Right != nullptr) {
                NodeQueue.push(nodeTemp->Right);
                r++;
            }

            if ((nodeTemp->Left != nullptr) && (nodeTemp->Right == nullptr)) {
                isWithoutRightNodeFlg = true; //发现不满足的点
            }
        }
    }
    return isWithoutRightNodeFlg;
}

//----------------------------------左神-------------
// 验证完全二叉树
// 测试链接 : https://leetcode.cn/problems/check-completeness-of-a-binary-tree/
public class Code08_CompletenessOfBinaryTree {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 提交以下的方法
	// 如果测试数据量变大了就修改这个值
	public static int MAXN = 101;

	public static TreeNode[] queue = new TreeNode[MAXN];

	public static int l, r;

	public static boolean isCompleteTree(TreeNode h) {
		if (h == null) {
			return true;
		}
		l = r = 0;
		queue[r++] = h;
		// 是否遇到过左右两个孩子不双全的节点
		boolean leaf = false;
		while (l < r) {
			h = queue[l++];
			if ((h.left == null && h.right != null) || (leaf && (h.left != null || h.right != null))) {
				return false;
			}
			if (h.left != null) {
				queue[r++] = h.left;
			}
			if (h.right != null) {
				queue[r++] = h.right;
			}
			if (h.left == null || h.right == null) {
				leaf = true;
			}
		}
		return true;
	}

}
