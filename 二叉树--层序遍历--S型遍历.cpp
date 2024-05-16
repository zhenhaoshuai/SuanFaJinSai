// S型 遍历每一层，没有 其他语言的随机访问，所以没有实现左神的代码
std::vector<std::vector<int>> levelOrderTraversal2(TreeNode *root)
{
    std::vector<std::vector<int>> ans;
    std::queue<TreeNode *> qTemp;

    qTemp.push(root);
    int l = 0,r = 1;//双指针来指定遍历每层
    int layer = 0;//层级

    int reverseFlg = 1;//进行翻转的flg

    while (l < r) { //因为要让 j 有追上每层 i的可能 就不能 把进行的条件设置成 while (!qTemp.empty()) {

        int size = r - l; //层序遍历经典 方法用左和右的关系 得出每一层for要用的size
        std::vector<int> layerData;

        for (int i = 0; i < size; ++i) {
            TreeNode *Node = qTemp.front();
            qTemp.pop();

            l++;
            layerData.push_back(Node->val);

            if (reverseFlg == 0) {
                if (nullptr != Node->Left) {
                    qTemp.push(Node->Left);
                    r++;
                }

                if (nullptr != Node->Right) {
                    qTemp.push(Node->Right);
                    r++;
                }

            }else{
                if (nullptr != Node->Right) {
                    qTemp.push(Node->Right);
                    r++;
                }
                if (nullptr != Node->Left) {
                    qTemp.push(Node->Left);
                    r++;
                }
            }
        }
        reverseFlg = !reverseFlg;
        ans.push_back(layerData);
    }
    return ans;
}


//---------------------------------左神
// 二叉树的锯齿形层序遍历
// 测试链接 : https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/
public class Code02_ZigzagLevelOrderTraversal {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 提交以下的方法
	// 用每次处理一层的优化bfs就非常容易实现
	// 如果测试数据量变大了就修改这个值
	public static int MAXN = 2001;

	public static TreeNode[] queue = new TreeNode[MAXN];

	public static int l, r;

	public static List<List<Integer>> zigzagLevelOrder(TreeNode root) {
		List<List<Integer>> ans = new ArrayList<>();
		if (root != null) {
			l = r = 0;
			queue[r++] = root;
			// false 代表从左往右
			// true 代表从右往左
			boolean reverse = false; 
			while (l < r) {
				int size = r - l;
				ArrayList<Integer> list = new ArrayList<Integer>();
				// reverse == false, 左 -> 右， l....r-1, 收集size个
				// reverse == true,  右 -> 左， r-1....l, 收集size个
				// 左 -> 右, i = i + 1
				// 右 -> 左, i = i - 1
				for (int i = reverse ? r - 1 : l, j = reverse ? -1 : 1, k = 0; k < size; i += j, k++) {
					TreeNode cur = queue[i];
					list.add(cur.val);
				}
				for (int i = 0; i < size; i++) {
					TreeNode cur = queue[l++];
					if (cur.left != null) {
						queue[r++] = cur.left;
					}
					if (cur.right != null) {
						queue[r++] = cur.right;
					}
				}
				ans.add(list);
				reverse = !reverse;
			}
		}
		return ans;
	}

}

