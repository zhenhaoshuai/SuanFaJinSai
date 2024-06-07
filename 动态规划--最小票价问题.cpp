/*
输入：days = [1,4,6,7,8,20] 表示在 这1年 内 第几天有出现安排, costs = [2,7,15] 这里有 3 种方案，A方案：这个票会帮你保管 1天 会花费a元，B方案：保管 7天 花费b元 ,C方案：保管 30 天花费C元
输出：11

题目： 花最少的钱，将这些计划 都安排 下去
*/

#define ARRAY_LEN 100

//-----------------递归做法------最后时间不符合要求-------
//递归做法  把这种方案看作是 一个 多叉树 来处理，每种树都有 多种case
int minCostTicketsSolveBuild(vector<int>& days, vector<int>& costs, vector<int>& dayNums,int pos)
{
    if (pos >= days.size())
    {
        return 0;
    }
    
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < costs.size(); i++){
        int posTemp = pos;
        while ((posTemp < days.size()) && (days[posTemp] < dayNums[i] + days[pos])){ //利用 天数 和 这个票的天数 之间的关系 来得到 下一个的位置
            ++posTemp;
        }
        
        ans = std::min(ans , costs[i] + minCostTicketsSolveBuild(days,costs,dayNums,posTemp));
    }
    return ans;
}

int mincostTickets(vector<int>& days, vector<int>& costs)
{
    std::vector<int> buffer(ARRAY_LEN, -1);  // 这个用来存这个2天的
    std::vector<int> dayNums{1,7,30}; //天数

    return minCostTicketsSolveBuild(days ,costs ,dayNums,0);
}

//-------------------------使用动态规划，来优化了这个过程，----所以动态规划有时只是 一个优化策略
//使用动态规划 ， 记忆化搜索的方式 ，使用 从顶到底
// 由于 所有的情况都是进入一个但是 ，每次进入我们计算过的情况里，我们 优化掉那些进入过里面的情况，这样我们就可以避免 那些重复进入的情况
#define ARRAY_LEN 300

//递归做法  把这种方案看作是 一个 多叉树 来处理，每种树都有 多种case
int minCostTicketsSolveBuild(vector<int>& days, vector<int>& costs, vector<int>& dayNums, vector<int>& buffer ,int pos)
{
    if (pos >= days.size())
    {
        return 0;
    }

    if (-1 != buffer[pos])  // 通过记忆化搜索 优化掉 并剪枝，因为我们已经进入过了
    {
        return buffer[pos];
    }
    
    
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < costs.size(); i++){
        int posTemp = pos;
        while ((posTemp < days.size()) && (days[posTemp] < dayNums[i] + days[pos])){ //利用 天数 和 这个票的天数 之间的关系 来得到 下一个的位置
            ++posTemp;
        }
        
        ans = std::min(ans , costs[i] + minCostTicketsSolveBuild(days,costs,dayNums,buffer,posTemp));
    }
    buffer[pos] = ans;
    return ans;
}

int mincostTickets(vector<int>& days, vector<int>& costs)
{
    std::vector<int> buffer(ARRAY_LEN, -1);  // 这个用来存这个2天的
    std::vector<int> dayNums{1,7,30}; //天数

    return minCostTicketsSolveBuild(days ,costs ,dayNums,buffer,0);
}


//----------------------------------左神
// 最低票价
// 在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
// 在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
// 每一项是一个从 1 到 365 的整数
// 火车票有 三种不同的销售方式
// 一张 为期1天 的通行证售价为 costs[0] 美元
// 一张 为期7天 的通行证售价为 costs[1] 美元
// 一张 为期30天 的通行证售价为 costs[2] 美元
// 通行证允许数天无限制的旅行
// 例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
// 那么我们可以连着旅行 7 天(第2~8天)
// 返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/
public class Code02_MinimumCostForTickets {

	// 无论提交什么方法都带着这个数组      0  1  2
	public static int[] durations = { 1, 7, 30 };

	// 暴力尝试
	public static int mincostTickets1(int[] days, int[] costs) {
		return f1(days, costs, 0);
	}

	// days[i..... 最少花费是多少 
	public static int f1(int[] days, int[] costs, int i) {
		if (i == days.length) {
			// 后续已经无旅行了
			return 0;
		}
		// i下标 : 第days[i]天，有一场旅行
		// i.... 最少花费是多少 
		int ans = Integer.MAX_VALUE;
		for (int k = 0, j = i; k < 3; k++) {
			// k是方案编号 : 0 1 2
			while (j < days.length && days[i] + durations[k] > days[j]) {
				// 因为方案2持续的天数最多，30天
				// 所以while循环最多执行30次
				// 枚举行为可以认为是O(1)
				j++;
			}
			ans = Math.min(ans, costs[k] + f1(days, costs, j));
		}
		return ans;
	}

	// 暴力尝试改记忆化搜索
	// 从顶到底的动态规划
	public static int mincostTickets2(int[] days, int[] costs) {
		int[] dp = new int[days.length];
		for (int i = 0; i < days.length; i++) {
			dp[i] = Integer.MAX_VALUE;
		}
		return f2(days, costs, 0, dp);
	}

	public static int f2(int[] days, int[] costs, int i, int[] dp) {
		if (i == days.length) {
			return 0;
		}
		if (dp[i] != Integer.MAX_VALUE) {
			return dp[i];
		}
		int ans = Integer.MAX_VALUE;
		for (int k = 0, j = i; k < 3; k++) {
			while (j < days.length && days[i] + durations[k] > days[j]) {
				j++;
			}
			ans = Math.min(ans, costs[k] + f2(days, costs, j, dp));
		}
		dp[i] = ans;
		return ans;
	}

	// 严格位置依赖的动态规划
	// 从底到顶的动态规划
	public static int MAXN = 366;

	public static int[] dp = new int[MAXN];

	public static int mincostTickets3(int[] days, int[] costs) {
		int n = days.length;
		Arrays.fill(dp, 0, n + 1, Integer.MAX_VALUE);
		dp[n] = 0;
		for (int i = n - 1; i >= 0; i--) {
			for (int k = 0, j = i; k < 3; k++) {
				while (j < days.length && days[i] + durations[k] > days[j]) {
					j++;
				}
				dp[i] = Math.min(dp[i], costs[k] + dp[j]);
			}
		}
		return dp[0];
	}

}



