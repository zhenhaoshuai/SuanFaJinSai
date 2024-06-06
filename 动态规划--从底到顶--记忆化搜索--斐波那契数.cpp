
/*
斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

F(0) = 0，F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中 n > 1
给定 n ，请计算 F(n) 。

 

示例 1：

输入：n = 2
输出：1
解释：F(2) = F(1) + F(0) = 1 + 0 = 1
示例 2：

输入：n = 3
输出：2
解释：F(3) = F(2) + F(1) = 1 + 1 = 2
示例 3：

输入：n = 4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3

*/

//----------------------------------经典 for 写法
#define ARRAY_LEN 100

void fibBuild(int n,vector<int>& buffer) {
    if (n >= 0) buffer[0] = 0;
    if (n >= 1) buffer[1] = 1;
    for (int i = 2; i <= n; i++) {
        buffer[i] = buffer[i-1] + buffer[i-2]; //该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。
    }
}

int fib(int n) {
    if (n < 0) return -1; // 处理负输入
    std::vector<int> buffer(ARRAY_LEN, -1); // 初始化buffer，长度为ARRAY_LEN，所有元素初始值为-1

    // 如果缓存中没有这个数值，则生成它
    if (buffer[n] == -1) {
        fibBuild(n, buffer);
    }
    return buffer[n];    
}

//-----------------递归写法
#define ARRAY_LEN 100

void fibBuild(int& n,vector<int>& buffer,int pos) {
    if (pos > n)
    {
        return;
    }
    buffer[pos] = buffer[pos-1] + buffer[pos-2]; //该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。
    fibBuild(n, buffer, pos+1);
}

int fib(int n) {
    if (n < 0) return -1; // 处理负输入
    std::vector<int> buffer(ARRAY_LEN, -1); // 初始化buffer，长度为ARRAY_LEN，所有元素初始值为-1

    // 如果缓存中没有这个数值，则生成它
    int pos = 2;
    if (buffer[n] == -1) {
        buffer[0] = 0;
        buffer[1] = 1;
        fibBuild(n, buffer, pos);
    }
    return buffer[n];    
}

//--------------左神---

// 斐波那契数
// 斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列
// 该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。
// 也就是：F(0) = 0，F(1) = 1
// F(n) = F(n - 1) + F(n - 2)，其中 n > 1
// 给定 n ，请计算 F(n)
// 测试链接 : https://leetcode.cn/problems/fibonacci-number/
// 注意：最优解来自矩阵快速幂，时间复杂度可以做到O(log n)
// 后续课程一定会讲述！本节课不涉及！
public class Code01_FibonacciNumber {

	public static int fib1(int n) {
		return f1(n);
	}

	public static int f1(int i) {
		if (i == 0) {
			return 0;
		}
		if (i == 1) {
			return 1;
		}
		return f1(i - 1) + f1(i - 2);
	}

	public static int fib2(int n) {
		int[] dp = new int[n + 1];
		Arrays.fill(dp, -1);
		return f2(n, dp);
	}

	public static int f2(int i, int[] dp) {
		if (i == 0) {
			return 0;
		}
		if (i == 1) {
			return 1;
		}
		if (dp[i] != -1) {
			return dp[i];
		}
		int ans = f2(i - 1, dp) + f2(i - 2, dp);
		dp[i] = ans;
		return ans;
	}

	public static int fib3(int n) {
		if (n == 0) {
			return 0;
		}
		if (n == 1) {
			return 1;
		}
		int[] dp = new int[n + 1];
		dp[1] = 1;
		for (int i = 2; i <= n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}

	public static int fib4(int n) {
		if (n == 0) {
			return 0;
		}
		if (n == 1) {
			return 1;
		}
		int lastLast = 0, last = 1;
		for (int i = 2, cur; i <= n; i++) {
			cur = lastLast + last;
			lastLast = last;
			last = cur;
		}
		return last;
	}

}


