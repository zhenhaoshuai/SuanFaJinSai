// 但是在答案中 如【3322144】中 假如返回了[144] 就不用返回[414] 和 [441]了，因为题目要求无视顺序了


/*
 * 我的思路还是 和 之前那道 用2分的方法给 这个字符串 进行排列组合,所以这个就是 那个题的变种
 *    +3              +3
 * -3               +3                      像这样的这2棵树就重复了
 *   +3              -3
 * 不用 "把所有元素排序后，把所有不同的元素 根据不同的元素进行划分层，因为 根据每层来进行划分  " 这样会 很复制
 *
 * */
void subsetsWithDupSolve(std::vector<int>& source,std::vector<std::vector<int>>& result,std::vector<int>& resultTemp,int pos,int len)
{
    if (pos > len) {
        result.push_back(resultTemp);
        return;
    }

    //l push_back("")
    subsetsWithDupSolve(source, result, resultTemp, pos + 1, len);//l
    //l pop_back();
    resultTemp.push_back(source[pos]); //r
    subsetsWithDupSolve(source, result, resultTemp, pos + 1, len);//r
    resultTemp.pop_back(); //r
}


std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
{
    std::vector<std::vector<int>> result;
    std::vector<int> resultTemp;
    std::sort(nums.begin(), nums.end());
    subsetsWithDupSolve(nums,result,resultTemp,0,nums.size()-1);
    // 对向量进行排序
    std::sort(result.begin(), result.end());

    // 使用 std::unique 移动重复的元素到末尾，并获取新末尾的迭代器
    auto newEnd = std::unique(result.begin(), result.end());

    // 使用 erase 删除重复的元素
    result.erase(newEnd, result.end());
    return result;
}

//--------------------------------------------------------左神


/*
像这种的我们一般都要先排序

想这个我们排完序之后 [1,1,1,1,2,2,2,3,3,4,4,4]
思路就是我们 使用排完序之后，把每个不一样的的当做一层，这样就相当于 层递归了
0个1  f(r)
1个1  f(r)
2个1  f(r)
3个1  f(r)
4个1  f(r)
--------------这是左神的 做法思路
*/


// 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的组合
// 答案 不能 包含重复的组合。返回的答案中，组合可以按 任意顺序 排列
// 注意其实要求返回的不是子集，因为子集一定是不包含相同元素的，要返回的其实是不重复的组合
// 比如输入：nums = [1,2,2]
// 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
// 测试链接 : https://leetcode.cn/problems/subsets-ii/
public class Code02_Combinations {

	public static List<List<Integer>> subsetsWithDup(int[] nums) {
		List<List<Integer>> ans = new ArrayList<>();
		Arrays.sort(nums);
		f(nums, 0, new int[nums.length], 0, ans);
		return ans;
	}

	public static void f(int[] nums, int i, int[] path, int size, List<List<Integer>> ans) {
		if (i == nums.length) {
			ArrayList<Integer> cur = new ArrayList<>();
			for (int j = 0; j < size; j++) {
				cur.add(path[j]);
			}
			ans.add(cur);
		} else {
			// 下一组的第一个数的位置
			int j = i + 1;
			while (j < nums.length && nums[i] == nums[j]) {
				j++;
			}
			// 当前数x，要0个
			f(nums, j, path, size, ans);
			// 当前数x，要1个、要2个、要3个...都尝试
			for (; i < j; i++) {
				path[size++] = nums[i];
				f(nums, j, path, size, ans);
			}
		}
	}

}





