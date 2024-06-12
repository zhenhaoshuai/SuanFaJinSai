
/*
通常 路径最短问题，有好几种解法

这题 说了只能向 下 或向右移动

如果这题按照 递归方式来写的话，因为每个都只能 向下 或 向右， 到某个墙壁的时候我们要换方向 ， 这个题和那个贪吃蛇那题 很相似
因为每个元素都是这样的： cur->递归方向 1 ，每个元素都是这样的
                      | 递归方向 2
                      -
*/

/*
horizon  : i
vertical : j
所以 是这个 规定的运动方向 让这题有使用递归的可能性
这种超时了
*/
int minPathSumSolve(vector<vector<int>>& grid,int i,int j) {

    if ((i >= (grid.size())) || (j >= (grid[i].size())))
    {
        return INT_MAX;
    }

    if ((i == grid.size() -1) && (j == grid[i].size() -1))
    {
        return grid[i][j];
    }
    

    int left = minPathSumSolve(grid,i+1,j);
    int bottom = minPathSumSolve(grid,i,j+1);;

    return grid[i][j] + std::min(left,bottom);
}

int minPathSum(vector<vector<int>>& grid) {
    return minPathSumSolve(grid,0,0);
}

// -------- 使用 记忆化搜索 ，将第一次经过的路径的结果，在 递归回退的时候，把这个结果存起来
int minPathSumSolve(vector<vector<int>>& grid,vector<vector<int>>& buffer,int i,int j) {


    if ((i >= (grid.size())) || (j >= (grid[i].size())))
    {
        return INT_MAX;
    }

    if ((i == grid.size() -1) && (j == grid[i].size() -1))
    {
        return grid[i][j];
    }

    if (-1 != buffer[i][j])
    {
        return buffer[i][j];
    }

    int left = minPathSumSolve(grid,buffer,i+1,j);
    int bottom = minPathSumSolve(grid,buffer,i,j+1);
    buffer[i][j] = grid[i][j] + std::min(left,bottom);
    return buffer[i][j];
}

int minPathSum(vector<vector<int>>& grid) {
    vector<vector<int>> buffer(200, vector<int>(200, -1));
    return minPathSumSolve(grid,buffer,0,0);
}

/* 所以我们就可以 一行 一行 地遍历它， ，它这个是从一个大矩阵的一个顶角 到 另一个 顶角，我们就可以把它 看成是 一个正矩形的 顶角 到 另一个顶角， 然后再慢慢延伸到 整个矩形上

-------------------路径依赖 
*/
int minPathSum(vector<vector<int>>& grid) {
    vector<vector<int>> buffer(200, vector<int>(200, -1));

    buffer[0][0] = grid[0][0];
    for (int i = 1; i < grid.size(); i++) 
    {
        buffer[i][0] = buffer[i-1][0] + grid[i][0]; //把竖着的位置 都累加起来
    }
    for (int i = 1; i < grid[0].size(); i++) 
    {
        buffer[0][i] = buffer[0][i-1] + grid[0][i]; //把横着的位置 都累加起来
    }
    //这样我们就得到了一个边界有值，我们只需要 慢慢把 都组成 一个个矩形 来得出结果，在2个方向我们取最小的那个来作为我们这个值的最小值
    for (int i = 1; i < grid.size(); i++)
    {
        for (int j = 1; j < grid[i].size(); j++)
        {
            buffer[i][j] = std::min(buffer[i-1][j],buffer[i][j-1]) + grid[i][j]; //在当前位置我们取他们的最小值作为 当前答案
        }
    }

    return buffer[grid.size()-1][grid[0].size()-1];
}


//---------------------- 下面是 路径依赖 + 空间压缩  来优化

    int minPathSum(vector<vector<int>>& grid) {
      const int LEN = grid[0].size();
      int top[LEN]; 
      top[0] = grid[0][0];
      for (int i = 1; i < grid[0].size(); i++)
      {
          top[i] = top[i-1] + grid[0][i]; //记录上一行的值
      }
      
      int left = 0;
      //这样我们就得到了一个边界有值，我们只需要 慢慢把 都组成 一个个矩形 来得出结果，在2个方向我们取最小的那个来作为我们这个值的最小值
      for (int i = 1; i < grid.size(); i++)
      {
          left = top[0] + grid[i][0];
          top[0] = left;
          for (int j = 1; j < grid[i].size(); j++)
          {
              left = top[j] = std::min(top[j],left) + grid[i][j]; //在当前位置我们取他们的最小值作为 当前答案
          }
      }
  
      return top[LEN - 1];
    }

//-------------------   左神
// 最小路径和
// 给定一个包含非负整数的 m x n 网格 grid
// 请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
// 说明：每次只能向下或者向右移动一步。
// 测试链接 : https://leetcode.cn/problems/minimum-path-sum/
public class Code01_MinimumPathSum {

	// 暴力递归
	public static int minPathSum1(int[][] grid) {
		return f1(grid, grid.length - 1, grid[0].length - 1);
	}

	// 从(0,0)到(i,j)最小路径和
	// 一定每次只能向右或者向下
	public static int f1(int[][] grid, int i, int j) {
		if (i == 0 && j == 0) {
			return grid[0][0];
		}
		int up = Integer.MAX_VALUE;
		int left = Integer.MAX_VALUE;
		if (i - 1 >= 0) {
			up = f1(grid, i - 1, j);
		}
		if (j - 1 >= 0) {
			left = f1(grid, i, j - 1);
		}
		return grid[i][j] + Math.min(up, left);
	}

	// 记忆化搜索
	public static int minPathSum2(int[][] grid) {
		int n = grid.length;
		int m = grid[0].length;
		int[][] dp = new int[n][m];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				dp[i][j] = -1;
			}
		}
		return f2(grid, grid.length - 1, grid[0].length - 1, dp);
	}

	public static int f2(int[][] grid, int i, int j, int[][] dp) {
		if (dp[i][j] != -1) {
			return dp[i][j];
		}
		int ans;
		if (i == 0 && j == 0) {
			ans = grid[0][0];
		} else {
			int up = Integer.MAX_VALUE;
			int left = Integer.MAX_VALUE;
			if (i - 1 >= 0) {
				up = f2(grid, i - 1, j, dp);
			}
			if (j - 1 >= 0) {
				left = f2(grid, i, j - 1, dp);
			}
			ans = grid[i][j] + Math.min(up, left);
		}
		dp[i][j] = ans;
		return ans;
	}

	// 严格位置依赖的动态规划
	public static int minPathSum3(int[][] grid) {
		int n = grid.length;
		int m = grid[0].length;
		int[][] dp = new int[n][m];
		dp[0][0] = grid[0][0];
		for (int i = 1; i < n; i++) {
			dp[i][0] = dp[i - 1][0] + grid[i][0];
		}
		for (int j = 1; j < m; j++) {
			dp[0][j] = dp[0][j - 1] + grid[0][j];
		}
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < m; j++) {
				dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[n - 1][m - 1];
	}

	// 严格位置依赖的动态规划 + 空间压缩技巧
	public static int minPathSum4(int[][] grid) {
		int n = grid.length;
		int m = grid[0].length;
		// 先让dp表，变成想象中的表的第0行的数据
		int[] dp = new int[m];
		dp[0] = grid[0][0];
		for (int j = 1; j < m; j++) {
			dp[j] = dp[j - 1] + grid[0][j];
		}
		for (int i = 1; i < n; i++) {
			// i = 1，dp表变成想象中二维表的第1行的数据
			// i = 2，dp表变成想象中二维表的第2行的数据
			// i = 3，dp表变成想象中二维表的第3行的数据
			// ...
			// i = n-1，dp表变成想象中二维表的第n-1行的数据
			dp[0] += grid[i][0];
			for (int j = 1; j < m; j++) {
				dp[j] = Math.min(dp[j - 1], dp[j]) + grid[i][j];
			}
		}
		return dp[m - 1];
	}

}




