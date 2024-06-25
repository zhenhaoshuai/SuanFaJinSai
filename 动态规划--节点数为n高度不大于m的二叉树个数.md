---
tags:
  - 动态规划
  - 牛客
  - 同余原理
  - 纵向路径依赖
  - 二维动态规划
---

# 题目总结

对于这种 求种类的，多少种不同种类的，我们可以使用 <mark style="background: #FFB86CA6;">乘法定律</mark>，<mark style="background: #ADCCFFA6;">左树多少种不同数量的结构，与 右树不同数量的结构，最后 一乘 就是最终 不同种类的 数量</mark>
当然这题 用常规的 暴力递归 也可以做到的

使用左神的思维，分成了2块 左和右 , <mark style="background: #FFB8EBA6;">用一个for 来表示 这次给左右各分几个节点</mark>

最后面的，路径依赖中，枚举行为是可以得到进一步优化的，后面会有单独的章节讲，但是这题这个枚举就已经是最优解了
# 相关概念 
1. 
# 题目描述：
![[Pasted image 20240623093352.png|700]]
就是 有n个节点，让你画出高度不超过 m ，有多少种画法
# 我的思路
1. 这个题 有点像是 [[递归--排列组合--返回字符串的所有子序列]] ，通过递归来实现 所有元素之间有无的关系，然后用 len 和 剩余节点数来 判断这个树是否满足
2. 

## 代码 1   暴力递归
超时了
```cpp
#define MOD 1000000007

typedef long long  ll;

void f1(int& arrNodeNum, int& n, int& m,ll& result, int h){
    if (h > m || arrNodeNum > n){
        return;
    }

    if (arrNodeNum == n && h <= m){
        ++result;
        result %= MOD;
        return;
    }

    ++arrNodeNum;
    f1(arrNodeNum, n, m, result, h+1); // add left node
    // --arrNodeNum;
    // ++arrNodeNum; // 相当于 给这些节点 弹出 和 加入 上一次添加的节点
    f1(arrNodeNum, n, m, result, h+1); // add right node
    --arrNodeNum;
}

ll solve(int a, int b){
    int arrNodeNum = 0;
    ll result = 0;
    f1(arrNodeNum, a, b, result, 1);
    return result;
}
```
## 代码2   --   记忆化搜索
很简单的记忆化搜索
```cpp
#define MOD 1000000007

typedef long long  ll;

int f1(int arrNodeNum, int& n, int& m, int h, vector<vector<int>>& dp){
    if (h > m || arrNodeNum > n) {
        return 0;
    }

    if (dp[arrNodeNum][h] != -1) {
        return dp[arrNodeNum][h];
    }

    if (arrNodeNum == n && h <= m) {
        return dp[arrNodeNum][h] = 1;
    }

    ll ans = 0;
    ans = (f1(arrNodeNum + 1, n, m, h + 1, dp) + f1(arrNodeNum + 1, n, m, h + 1, dp)) % MOD; // 添加左和右节点

    dp[arrNodeNum][h] = ans;
    return ans;
}

ll solve(int a, int b){
    int arrNodeNum = 0;
    ll result = 0;
    vector<vector<int>> dp(a+1, vector<int>(b+1, -1));
    result = f1(arrNodeNum, a, b, 1, dp);
    return result;
}
```


## 代码3 
 使用左神的思维，分成了2块 左和右 , <mark style="background: #FFB8EBA6;">用一个for 来表示 这次给左右各分几个节点</mark>
 ```cpp
/*
n:节点数
m:高度
 */
int f1(int n, int m, vector<vector<int>>& dp){
    if (m == 0) { // m这里使用倒序， 这样m 就可以少传个 参数
        return 0;
    }

    if (n == 0){
        return 1;//因为 前面的 m==0 已经说明到这里是节点为0，返回1 * 谁 都是 谁
    }

    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    ll ans = 0;
    //这里的i 表示 占了 几个 节点
    for (int i = 0; i <= n; i++){
        ans =  (ans + ((long)f1(i, m - 1, dp) * f1(n-i+1, m - 1, dp))%MOD ) % MOD;
    }

    dp[n][m] = ans;
    return ans;
}
```

## 代码4

## 代码5  Chat GPT


# 大神的思路
```cpp
		for (int k = 0; k < n; k++) {
			// 一共n个节点，头节点已经占用了1个名额
			// 如果左树占用k个，那么右树就占用i-k-1个
			ans = (ans + ((long) compute1(k, m - 1) * compute1(n - k - 1, m - 1)) % MOD) % MOD;
		}
```
<mark style="background: #FFB8EBA6;">左神提供了 不一样的解法，把整个区域分成 2半，左 右</mark>

## 左神指导写法 -- 暴力

## 左神指导写法 --  记忆化搜索

## 左神指导写法 --  路径依赖
![[Pasted image 20240623154148.png|500]]
![[Pasted image 20240623154400.png|500]]
## 左神指导写法 --  空间压缩


## ---------- 左神 Code ---------

```java
// 节点数为n高度不大于m的二叉树个数
// 现在有n个节点，计算出有多少个不同结构的二叉树
// 满足节点个数为n且树的高度不超过m的方案
// 因为答案很大，所以答案需要模上1000000007后输出
// 测试链接 : https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.StreamTokenizer;

public class Code05_NodenHeightNotLargerThanm {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StreamTokenizer in = new StreamTokenizer(br);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		while (in.nextToken() != StreamTokenizer.TT_EOF) {
			int n = (int) in.nval;
			in.nextToken();
			int m = (int) in.nval;
			out.println(compute3(n, m));
		}
		out.flush();
		out.close();
		br.close();
	}

	public static int MAXN = 51;

	public static int MOD = 1000000007;

	// 记忆化搜索
	public static long[][] dp1 = new long[MAXN][MAXN];

	static {
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < MAXN; j++) {
				dp1[i][j] = -1;
			}
		}
	}

	// 二叉树节点数为n
	// 高度不能超过m
	// 结构数返回
	// 记忆化搜索
	public static int compute1(int n, int m) {
		if (n == 0) {
			return 1;
		}
		// n > 0
		if (m == 0) {
			return 0;
		}
		if (dp1[n][m] != -1) {
			return (int) dp1[n][m];
		}
		long ans = 0;
		// n个点，头占掉1个
		for (int k = 0; k < n; k++) {
			// 一共n个节点，头节点已经占用了1个名额
			// 如果左树占用k个，那么右树就占用i-k-1个
			ans = (ans + ((long) compute1(k, m - 1) * compute1(n - k - 1, m - 1)) % MOD) % MOD; //这里使用了同余原理
		}
		dp1[n][m] = ans;
		return (int) ans;
	}

	// 严格位置依赖的动态规划
	public static long[][] dp2 = new long[MAXN][MAXN];

	public static int compute2(int n, int m) {
		for (int j = 0; j <= m; j++) {
			dp2[0][j] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp2[i][j] = 0;
				for (int k = 0; k < i; k++) {
					// 一共i个节点，头节点已经占用了1个名额
					// 如果左树占用k个，那么右树就占用i-k-1个
					dp2[i][j] = (dp2[i][j] + dp2[k][j - 1] * dp2[i - k - 1][j - 1] % MOD) % MOD;
				}
			}
		}
		return (int) dp2[n][m];
	}

	//这个空间 将上面的2维的压缩成 1维的了，太强了，这里的空间压缩是  行的话 从下往上，列的话，从左到右
	//因为行从下往上推，因为上面的还没更新呢，下面的值就能表示上面的结果值
	// 空间压缩
	public static long[] dp3 = new long[MAXN];

	public static int compute3(int n, int m) {
		dp3[0] = 1;
		for (int i = 1; i <= n; i++) {
			dp3[i] = 0;
		}
		for (int j = 1; j <= m; j++) { //列从左往右推
			// 根据依赖，一定要先枚举列
			for (int i = n; i >= 1; i--) { //行是从下往上 推
				// 再枚举行，而且i不需要到达0，i>=1即可
				dp3[i] = 0;
				for (int k = 0; k < i; k++) {
					// 枚举
					dp3[i] = (dp3[i] + dp3[k] * dp3[i - k - 1] % MOD) % MOD;
				}
			}
		}
		return (int) dp3[n];
	}

}
```
