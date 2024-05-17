
//某层 null  left  null left null null null right null
//就是这层 中最左端不为null 的最左端 到 最右端不为null 的最右端



//就是计算每层有真节点的最右端 到 每层有真节点的最左端 的最大值。最后的结果是所有层中 最大值的最大值
#define ARRAYLENGHT 3001
int numOfleft2right(TreeNode *root)
{
    int ans = 0;
    std::queue<TreeNode*> qTemp;
    qTemp.push(root);
    int l = 0, r = 1;
    std::queue<int> idQueue;//同步存储这些节点的位置信息
//    int idQueue[ARRAYLENGHT];//同步存储这些节点的位置信息
//    idQueue[l] = 2 * l + 1;
    idQueue.push(2 * 0 + 1);//0表示根节点编号
    while (l < r) {
        int size = r - l;
        int Rightval1 = idQueue.front();//最右端的值
        for (int i = 0; i < size; ++i) {
            int Rightval2 = idQueue.front();//从里面弹出的左端的值
            idQueue.pop();
            ans = std::max(ans, Rightval1 - Rightval2);

            TreeNode * NodeTemp = qTemp.front();
            qTemp.pop();
            l++;
            if (NodeTemp->Left != nullptr) {
                qTemp.push(NodeTemp->Left);
                idQueue.push(2 * Rightval2);
                r++;
            }
            if (NodeTemp->Right != nullptr) {
                qTemp.push(NodeTemp->Right);
                idQueue.push(2 * Rightval2 + 1);
                r++;
            }
        }
    }
    return ans;
}

//----------左神-----
// 二叉树的最大特殊宽度
// 测试链接 : https://leetcode.cn/problems/maximum-width-of-binary-tree/
public class Code03_WidthOfBinaryTree {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 提交以下的方法
	// 用每次处理一层的优化bfs就非常容易实现
	// 如果测试数据量变大了就修改这个值
	public static int MAXN = 3001;

	public static TreeNode[] nq = new TreeNode[MAXN];

	public static int[] iq = new int[MAXN];

	public static int l, r;

	public static int widthOfBinaryTree(TreeNode root) {
		int ans = 1;
		l = r = 0;
		nq[r] = root;
		iq[r++] = 1;
		while (l < r) {
			int size = r - l;
			ans = Math.max(ans, iq[r - 1] - iq[l] + 1);
			for (int i = 0; i < size; i++) {
				TreeNode node = nq[l];
				int id = iq[l++];
				if (node.left != null) {
					nq[r] = node.left;
					iq[r++] = id * 2;
				}
				if (node.right != null) {
					nq[r] = node.right;
					iq[r++] = id * 2 + 1;
				}
			}
		}
		return ans;
	}

}


