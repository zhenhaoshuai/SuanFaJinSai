
//错误代码
// 反思上：，遇到感觉思路 越来越清晰的时候，看看代码上 有一点偏的时候，我们就重写
// 代码的思路 是 没问题的，但是我的实现上是有问题的
//这个题 很好的 知道了 如何 使用 在递归中使用 它的上一层 信息
TreeNode *LCA_commonFatherOftwoNode(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == nullptr) {
        return nullptr;
    }

    TreeNode *Node1 = LCA_commonFatherOftwoNode(root->Left, p, q);
    TreeNode *Node2 = LCA_commonFatherOftwoNode(root->Right, p, q);

    if (((Node1 == Node2) && (Node1->Left == p))//就是 P和q逐层返回后,是一个层了
        || ((Node1 == p) && (Node1 == q))//node1就是 q p2个点
        || ((Node2 == p) && (Node2 == q))) { //他们之间互相返回了父节点，然后，比较他们之间的父节点的关系，相等就知道他们共同 的父节点
        return (Node1 != nullptr) ? Node1 : Node2;
    }//一般这个情况是不可能的，应该这2个点 题目要求是肯定在这个树上的

    //就是找到了这个点后，一层一层返回它的上一层的 父节点，
    if ((Node1 == p) || (Node1 == q)) {
        return root; //返回这层的信息，因为这层的子层 有 找到这个点
    }
    if ((Node2 == p) || (Node2 == q)) {
        return root;
    }

    return nullptr;
}

//修改后

//这个题 很好的 知道了 如何 使用 在递归中使用 它的上一层 信息
TreeNode *LCA_commonFatherOftwoNode(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if ((root == nullptr) || (root == p) || (root == q)) {
        return root; //，因为 如果是包含关系的话，就没必要向下搜索了，
    }

    TreeNode *Node1 = LCA_commonFatherOftwoNode(root->Left, p, q);
    TreeNode *Node2 = LCA_commonFatherOftwoNode(root->Right, p, q);

    //就是 左右2边都找到了，返回他们的父节点
    if ((Node1 != nullptr) && (Node2 != nullptr)) {
        return root; //处理分叉的时候
    }
    if ((Node1 == nullptr) && (Node2 == nullptr)) {
        return nullptr;
    }


    return (Node1 != nullptr)? Node1 : Node2;//到遇到一个就直接返回，因为 如果是包含关系的话，就没必要向下搜索了，
}

//-----------------左神
// 验证搜索二叉树
// 测试链接 : https://leetcode.cn/problems/validate-binary-search-tree/
public class Code05_ValidateBinarySearchTree {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 提交以下的方法
	public static int MAXN = 10001;

	public static TreeNode[] stack = new TreeNode[MAXN];

	public static int r;

	// 提交时改名为isValidBST
	public static boolean isValidBST1(TreeNode head) {
		if (head == null) {
			return true;
		}
		TreeNode pre = null;
		r = 0;
		while (r > 0 || head != null) {
			if (head != null) {
				stack[r++] = head;
				head = head.left;
			} else {
				head = stack[--r];
				if (pre != null && pre.val >= head.val) {
					return false;
				}
				pre = head;
				head = head.right;
			}
		}
		return true;
	}

	public static long min, max;

	// 提交时改名为isValidBST
	public static boolean isValidBST2(TreeNode head) {
		if (head == null) {
			min = Long.MAX_VALUE;
			max = Long.MIN_VALUE;
			return true;
		}
		boolean lok = isValidBST2(head.left);
		long lmin = min;
		long lmax = max;
		boolean rok = isValidBST2(head.right);
		long rmin = min;
		long rmax = max;
		min = Math.min(Math.min(lmin, rmin), head.val);
		max = Math.max(Math.max(lmax, rmax), head.val);
		return lok && rok && lmax < head.val && head.val < rmin;
	}

}
