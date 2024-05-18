

struct TreeNode {
    int val;
    TreeNode *Left, *Right;
    TreeNode(int num):val(num),Left(nullptr),Right(nullptr){}
};

/*
 * posA:根据前序 的起点位置
 * fatherNode:父节点的位置,因为 这个父节点的子节点 -》的子节点 也应该是在这个父节点的一侧的
 * 这个题目要求 输入的是去重的 ，就是不可能是一堆一样的
 */
TreeNode * preAndMidSequenceToTreeSolve(std::map<int,int>& mapA,std::map<int,int>& mapB,int posA,int fatherNodePos)
{
    if (posA >= mapA.size()) {
        return nullptr;
    }

    TreeNode *root = new TreeNode(mapA[posA]);

    //就是如果 先序位置的下一个元素在 中序位置 的左边 说明这个 先序中 PosA+1 只是这个元素 先序中PosA 的左节点
    if ((mapB[mapA[posA]] >= mapB[mapA[posA + 1]])
        && (mapB[mapA[fatherNodePos]] >= mapB[mapA[posA + 1]])) {
        root->Left = preAndMidSequenceToTreeSolve(mapA, mapB, posA + 1, posA);
    } else {
        root->Left = nullptr;
    }

    //就是如果 先序位置的下一个元素在 中序位置 的右边 说明这个 先序中 PosA+1 只是这个元素 先序中PosA 的右节点
    if ((mapB[mapA[posA]] < mapB[mapA[posA + 1]])
        && (mapB[mapA[fatherNodePos]] < mapB[mapA[posA + 1]])) {
        root->Right = preAndMidSequenceToTreeSolve(mapA, mapB, posA + 1, posA);
    } else {
        root->Right = nullptr;
    }

    return root;
}

//就是使用前序 序列 和 中序 序列 使用它们来完成一个树的还原
/*
 * a:前序序列 数组
 * b:中序序列 数组
 */
TreeNode *preAndMidSequenceToTree(std::vector<int> &a, std::vector<int> b) {
    //first = 这个位于这个数组中的idx,  second = 这个元素值
    std::map<int,int> mapA;
    std::map<int,int> mapB;
    for (int i = 0; i < a.size(); ++i) {
        mapA.insert({i, a[i]});
    }
    //first = 这个元素值,  second = 这个位于这个数组中的idx
    for (int i = 0; i < a.size(); ++i) {
        mapB.insert({b[i], i});
    }
    return preAndMidSequenceToTreeSolve(mapA, mapB, 0, 0);
}


//--------------------------------左神------
// 利用先序与中序遍历序列构造二叉树
// 测试链接 : https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
public class Code07_PreorderInorderBuildBinaryTree {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;

		public TreeNode(int v) {
			val = v;
		}
	}

	// 提交如下的方法
	public static TreeNode buildTree(int[] pre, int[] in) {
		if (pre == null || in == null || pre.length != in.length) {
			return null;
		}
		HashMap<Integer, Integer> map = new HashMap<>();
		for (int i = 0; i < in.length; i++) {
			map.put(in[i], i);
		}
		return f(pre, 0, pre.length - 1, in, 0, in.length - 1, map);
	}

	public static TreeNode f(int[] pre, int l1, int r1, int[] in, int l2, int r2, HashMap<Integer, Integer> map) {
		if (l1 > r1) {
			return null;
		}
		TreeNode head = new TreeNode(pre[l1]);
		if (l1 == r1) {
			return head;
		}
		int k = map.get(pre[l1]);
		// pre : l1(........)[.......r1]
		// in  : (l2......)k[........r2]
		// (...)是左树对应，[...]是右树的对应
		head.left = f(pre, l1 + 1, l1 + k - l2, in, l2, k - 1, map);
		head.right = f(pre, l1 + k - l2 + 1, r1, in, k + 1, r2, map);
		return head;
	}

}



