

//题目要求： 从头结点 一定要扎到 叶节点(从头扎到底)，如果有某个路径 等于= 你设定的aim和 ，那么就收起这条路径，要求在中间的时候满足条件也不能算，必须到底(中间不能停)

//注意 我们 当一条路径到底后满足条件后，返回它的上一层的时候，要把这条的痕迹去掉 ，---递归恢复现场

//第 1 版   ---- 失败了
std::vector<std::vector<int>> pathSumOfTop2Botm(TreeNode *root, int targetSum)
{
    std::vector<std::vector<int>> resArray;
    std::queue<TreeNode*> NodeQueue;
    NodeQueue.push(root);
    std::vector<int> resTemp;//一个从头到尾的串
    resTemp.push_back(root->val);
    int valTemp = root->val;//当前的值
    TreeNode* NodeTemp;

    while (!NodeQueue.empty())
    {
        NodeTemp = NodeQueue.front(); //--教训：：--就是这里导致 死循环的，因为这个不想 递归 每次都可以给它保存当前的环境，所以 把 递归改写成 while 的 都有这样的麻烦

        if ((NodeTemp->Left == nullptr) && (NodeTemp->Right == nullptr))
        {
            if (valTemp == targetSum)
            {
                resArray.push_back(resTemp);
            }
            resTemp.pop_back();
            NodeQueue.pop();
            valTemp -= NodeTemp->val;
        }else if (NodeTemp->Left != nullptr)
        {
            NodeQueue.push(NodeTemp->Left);
            resTemp.push_back(NodeTemp->val);
            valTemp += NodeTemp->val;
        }else if (NodeTemp->Right != nullptr)
        {
            NodeQueue.push(NodeTemp->Right);
            resTemp.push_back(NodeTemp->val);
            valTemp += NodeTemp->val;
        }
    }
    return resArray;
}

// 第2 版  结合第一步的 教训
void pathSumOfTop2BotmSolve(std::vector<std::vector<int>> &resArry, TreeNode *root,std::vector<int>& resTemp, int val, int targetSum) {
    if (root == nullptr) {
        return;
    }

    resTemp.push_back(root->val);
    if ((root->Left == nullptr) && (root->Right == nullptr))
    {
        if ((val + root->val) == targetSum) {
            resArry.push_back(resTemp); //到终点后把这个放入 结果集中
        }
    }else{
        if (root->Left != nullptr)
        {
            pathSumOfTop2BotmSolve(resArry, root->Left,resTemp, val + (root->val), targetSum);
        }
        if (root->Right != nullptr)
        {
            pathSumOfTop2BotmSolve(resArry, root->Right,resTemp, val + (root->val), targetSum);
        }
    }
    
    resTemp.pop_back();
}

/*
val:用于保存递归和的 当前和
*/
std::vector<std::vector<int>> pathSumOfTop2Botm(TreeNode *root, int targetSum) {
    std::vector<std::vector<int>> resArray;
    std::vector<int> resTemp;
    pathSumOfTop2BotmSolve(resArray, root,resTemp, 0, targetSum);
    return resArray;
}

//---------------------------------------------左神---
// 收集累加和等于aim的所有路径
// 测试链接 : https://leetcode.cn/problems/path-sum-ii/
public class Code03_PathSumII {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;
	}

	// 提交如下的方法
	public static List<List<Integer>> pathSum(TreeNode root, int aim) {
		List<List<Integer>> ans = new ArrayList<>();
		if (root != null) {
			List<Integer> path = new ArrayList<>();
			f(root, aim, 0, path, ans);
		}
		return ans;
	}

	public static void f(TreeNode cur, int aim, int sum, List<Integer> path, List<List<Integer>> ans) {
		if (cur.left == null && cur.right == null) {
			// 叶节点
			if (cur.val + sum == aim) {
				path.add(cur.val);
				copy(path, ans);
				path.remove(path.size() - 1);
			}
		} else {
			// 不是叶节点
			path.add(cur.val);
			if (cur.left != null) {
				f(cur.left, aim, sum + cur.val, path, ans);
			}
			if (cur.right != null) {
				f(cur.right, aim, sum + cur.val, path, ans);
			}
			path.remove(path.size() - 1);
		}
	}

	public static void copy(List<Integer> path, List<List<Integer>> ans) {
		List<Integer> copy = new ArrayList<>();
		for (Integer num : path) {
			copy.add(num);
		}
		ans.add(copy);
	}

}


