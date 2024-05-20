
//---------第1版
TreeNode *LCA_commonFatherOftwoNode_search2NodeTree(TreeNode *root, TreeNode *p, TreeNode *q) {
    //遇到了一个节点 他们之间是 发现了这个点就一直返回这个点//尽管他们是包含关系,也不搜了
    if ((root == nullptr) || (root->val == p->val) || (root->val == q->val)) {
        return root;
    }

    //遇到了 中间这个点 ，大小关系是呈现 "包含" 关系的话直接返回这个点, 就是要进行 分叉了
    if (((root->val >= p->val) && (root->val <= q->val))//在2边的位置
        || ((root->val >= q->val) && (root->val <= p->val))) {
        return root;
    }

    //这里不使用等于的话，是因为经典的搜索二叉树 是 没有重复的值的
    //对于这种 位置关系肯定 不在这里面的
    TreeNode *Node1, *Node2;
    if ((root->val < q->val) && (root->val < p->val)) {//都在一边的位置，所以根据 搜索二叉树的性质来优化它的搜索路径  //root都小于的话 就去右
        Node1 = LCA_commonFatherOftwoNode_search2NodeTree(root->Right, p, q);
    } else if ((root->val > q->val) && (root->val > p->val)) {
        Node2 = LCA_commonFatherOftwoNode_search2NodeTree(root->Left, p, q);//root都大于的话 就去右
    }

    if ((Node1 != nullptr) && (Node2 != nullptr)) {
        return root;
    }
    if ((Node1 == nullptr) && (Node2 == nullptr)) {
        return nullptr;
    }

    return (Node1 != nullptr) ? Node1 : Node2;
}

//第2版
TreeNode *LCA_commonFatherOftwoNode_search2NodeTree(TreeNode *root, TreeNode *p, TreeNode *q) {
    //遇到了一个节点 他们之间是 发现了这个点就一直返回这个点//尽管他们是包含关系,也不搜了
    if ((root == nullptr) || (root->val == p->val) || (root->val == q->val)) {
        return root;
    }

    //遇到了 中间这个点 ，大小关系是呈现 "包含" 关系的话直接返回这个点, 就是要进行 分叉了
    if (((root->val >= p->val) && (root->val <= q->val))//在2边的位置
        || ((root->val >= q->val) && (root->val <= p->val))) {
        return root;
    }

    //这里不使用等于的话，是因为经典的搜索二叉树 是 没有重复的值的
    //对于这种 位置关系肯定 不在这里面的
    if ((root->val < q->val) && (root->val < p->val)) {//都在一边的位置，所以根据 搜索二叉树的性质来优化它的搜索路径  //root都小于的话 就去右
        return LCA_commonFatherOftwoNode_search2NodeTree(root->Right, p, q);
    } else if ((root->val > q->val) && (root->val > p->val)) {
        return LCA_commonFatherOftwoNode_search2NodeTree(root->Left, p, q);//root都大于的话 就去右
    }else{
        return root; //就是这里想明白了    需比较当前节点与 p 和 q 的值来决定递归方向
    }
}


//----------------------------------------ChatGpt--    需比较当前节点与 p 和 q 的值来决定递归方向
TreeNode* LCA_commonFatherOftwoNode_search2NodeTree(TreeNode *root, TreeNode *p, TreeNode *q)
{
    // 遇到了一个节点 他们之间是 发现了这个点就一直返回这个点//尽管他们是包含关系,也不搜了
    if ((root == nullptr) || (root->val == p->val) || (root->val == q->val)) {
        return root;
    }

    // 利用二叉搜索树的性质
    if (root->val > p->val && root->val > q->val) {
        // p 和 q 都在左子树
        return LCA_commonFatherOftwoNode_search2NodeTree(root->left, p, q);
    } else if (root->val < p->val && root->val < q->val) {
        // p 和 q 都在右子树
        return LCA_commonFatherOftwoNode_search2NodeTree(root->right, p, q);
    } else {
        // p 和 q 分别在当前节点的两侧，说明当前节点就是最近公共祖先
        return root;
    }
}

TreeNode *LCA_commonFatherOftwoNode_search2NodeTree(TreeNode *root, TreeNode *p, TreeNode *q) {
    // 如果根节点为空或者根节点等于p或q，则返回根节点
    if (root == nullptr || root->val == p->val || root->val == q->val) {
        return root;
    }

    // 如果p和q都小于根节点，则公共祖先在左子树
    if (root->val > p->val && root->val > q->val) {
        return LCA_commonFatherOftwoNode_search2NodeTree(root->left, p, q);
    }
    
    // 如果p和q都大于根节点，则公共祖先在右子树
    if (root->val < p->val && root->val < q->val) {
        return LCA_commonFatherOftwoNode_search2NodeTree(root->right, p, q);
    }

    // 否则当前根节点就是公共祖先
    return root;
}

//-------------------左神-----

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

