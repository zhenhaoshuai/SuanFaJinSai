/*
 *  排列： [123]  有 [123] [132] [213] [231] [321] [312]  就是3! 3的阶乘
 *  就是 1XX  12X 13X
 *      2xx  21x 23x
 *      3xx  31x 32x
 *      也就是我们阶乘的思想不用位置进行所有的进行尝试
 *
 *      给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
示例 1：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：

输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例 3：

输入：nums = [1]
输出：[[1]]
 *
 *      这个题其实像 是行李箱上的密码锁 转盘，同时用到了环装序列
 *
 * dimension :层的深度，就是我们排列元素个数
 * cur_dimension : 当前所在层的深度，当进入的深度 足够时，我们就停止
 *
 * 注意：由于每个元素在每一层只能出现一次，所以下一层 要 填的元素，对于上一层来说是 随机的，所以我们要用 一个flag 字典
 *
 * */

void permuteSolve(vector<int>& source,vector<vector<int>>& result,vector<int>& resultTemp,int dimension,int cur_dimension,map<int,bool>& flgDict)
{
    if (dimension <= cur_dimension) {
        result.push_back(resultTemp);
        return;
    }

    for (int i = 0; i < dimension; ++i) {
        if (flgDict[i] == true) {
            continue;
        }
        flgDict[i] = true;
        resultTemp.push_back(source[i]);
        permuteSolve(source, result, resultTemp, dimension, cur_dimension + 1, flgDict);
        resultTemp.pop_back();//回溯
        flgDict[i] = false;
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> resultTemp;

    std::sort(nums.begin(), nums.end());
    map<int,bool> flgDict;//数据字典
    for (int i = 0; i < nums.size(); ++i) {
        flgDict[i] = false; //使用索引i作为flgDict的键，而不是数组元素的值source[i]。这样可以正确标记每个元素的使用状态，即使有重复的元素。
    }
    permuteSolve(nums, result, resultTemp, nums.size(), 0, flgDict);
    return result;
}


//------------------------------------------左神
// 没有重复项数字的全排列
// 测试链接 : https://leetcode.cn/problems/permutations/
public class Code03_Permutations {

	public static List<List<Integer>> permute(int[] nums) {
		List<List<Integer>> ans = new ArrayList<>();
		f(nums, 0, ans);
		return ans;
	}

	public static void f(int[] nums, int i, List<List<Integer>> ans) {
		if (i == nums.length) {
			List<Integer> cur = new ArrayList<>();
			for (int num : nums) {
				cur.add(num);
			}
			ans.add(cur);
		} else {
			for (int j = i; j < nums.length; j++) {
				swap(nums, i, j);
				f(nums, i + 1, ans);
				swap(nums, i, j); // 特别重要，课上进行了详细的图解
			}
		}
	}

	public static void swap(int[] nums, int i, int j) {
		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}

	public static void main(String[] args) {
		int[] nums = { 1, 2, 3 };
		List<List<Integer>> ans = permute(nums);
		for (List<Integer> list : ans) {
			for (int num : list) {
				System.out.print(num + " ");
			}
			System.out.println();
		}
	}

}


