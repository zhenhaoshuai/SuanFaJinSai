
struct TreeNode {
    int val;
    TreeNode *Left, *Right;
    TreeNode(int num):val(num),Left(nullptr),Right(nullptr){}
};


//先序 序列化
std::string  serilize(TreeNode* root)
{
   std::string ans("");
   if(root == nullptr){
      return  "#";
   }
   ans = to_string(root->val) + "，" + serilize(root->Left) + "," + anserilize(root->Right);
   return ans;
}

//反序列化 ---先序
#include "regex"

std::vector<std::string> splitString(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> tokens;
    std::regex re(delimiter);
    std::sregex_token_iterator it(str.begin(), str.end(), re, -1);
    std::sregex_token_iterator reg_end;
    for (; it != reg_end; ++it) {
        tokens.push_back(it->str());
    }
    return tokens;
}

TreeNode *toTree(std::vector<std::string>& items,int pos)
{
    if (pos >= items.size() || items[pos] == "#") {
        return nullptr;
    }

    TreeNode *root = new TreeNode(stoi(items[pos]));
    if (2 * pos + 1 < items.size()) {
        root->Left = toTree(items, 2 * pos + 1);
    }

    if (2 * pos + 2 < items.size()) {
        root->Right = toTree(items, 2 * pos + 2);
    }
    return root;//返回最后的结果
}

TreeNode *deserilize(std::string &&str)
{
    std::vector<std::string> items = splitString(str, ",");

    return toTree(items, 0);
}


//-------------------------------左神--------------

// 二叉树先序序列化和反序列化
// 测试链接 : https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
public class Code05_PreorderSerializeAndDeserialize {

	// 不提交这个类
	public static class TreeNode {
		public int val;
		public TreeNode left;
		public TreeNode right;

		public TreeNode(int v) {
			val = v;
		}
	}

    // 二叉树可以通过先序、后序或者按层遍历的方式序列化和反序列化
    // 但是，二叉树无法通过中序遍历的方式实现序列化和反序列化
    // 因为不同的两棵树，可能得到同样的中序序列，即便补了空位置也可能一样。
    // 比如如下两棵树
    //         __2
    //        /
    //       1
    //       和
    //       1__
    //          \
    //           2
    // 补足空位置的中序遍历结果都是{ null, 1, null, 2, null}
	// 提交这个类
	public class Codec {

		public String serialize(TreeNode root) {
			StringBuilder builder = new StringBuilder();
			f(root, builder);
			return builder.toString();
		}

		void f(TreeNode root, StringBuilder builder) {
			if (root == null) {
				builder.append("#,");
			} else {
				builder.append(root.val + ",");
				f(root.left, builder);
				f(root.right, builder);
			}
		}

		public TreeNode deserialize(String data) {
			String[] vals = data.split(",");
			cnt = 0;
			return g(vals);
		}

		// 当前数组消费到哪了
		public static int cnt;

		TreeNode g(String[] vals) {
			String cur = vals[cnt++];
			if (cur.equals("#")) {
				return null;
			} else {
				TreeNode head = new TreeNode(Integer.valueOf(cur));
				head.left = g(vals);
				head.right = g(vals);
				return head;
			}
		}

	}

}





