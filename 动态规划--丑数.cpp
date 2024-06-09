// -------   递归还是超时了
//---这道题 我错就错在，按照了 自然数的顺序去找 丑数，而忽略了 丑数的本质 就是 下一个丑数一定是 2/3/5的倍数，--所以思路就变成了我们 直接使用丑数了
/*
时的原因可能是由于递归深度过大和重复计算。虽然你已经使用了 buffer 来记忆化一些结果，但目前的递归结构可能导致多次冗余计算，尤其是对于较大的 n。

这里有几个改进方向：

减少递归调用的次数：可以直接检查是否是丑数，并将结果记录在 buffer 中。
迭代实现：通过迭代来减少递归开销。

给你一个整数 n ，请你找出并返回第 n 个 丑数 。

丑数 就是质因子只包含 2、3 和 5 的正整数。

 

示例 1：

输入：n = 10
输出：12
解释：[1, 2, 3, 4, 5, 6, 8, 9, 10, 12] 是由前 10 个丑数组成的序列。
示例 2：

输入：n = 1
输出：1
解释：1 通常被视为丑数。

*/


#define UGLYNUM_YES 1
#define UGLYNUM_NO 0
#define UGLYNUM_UNDEFINE -1

class Solution {
public:

int nthUglyNumberSolve(int& n, int& pos, std::vector<int>& buffer, const std::vector<int>& factors, int num) {
    if (n > 0 && n <= pos) {
        return num - 1; // 返回找到的第 n 个丑数
    }
    
    if (num >= buffer.size()) {
        buffer.resize(num + 1, UGLYNUM_UNDEFINE);
    }
    
    if (UGLYNUM_YES == buffer[num]) {
        return true;
    } else if (UGLYNUM_NO == buffer[num]) {
        return false;
    }

    int temp = num;
    for (int factor : factors) {
        if (temp % factor == 0) {
            temp /= factor;
            if (nthUglyNumberSolve(n, pos, buffer, factors, temp)) {
                temp = 1;
                break;
            } else {
                break;
            }
        }
    }

    if (temp == 1) {
        buffer[num] = UGLYNUM_YES;
        ++pos;
    } else {
        buffer[num] = UGLYNUM_NO;
    }

    return nthUglyNumberSolve(n, pos, buffer, factors, num + 1);
}

int nthUglyNumber(int n) {
    std::vector<int> buffer(2, UGLYNUM_UNDEFINE); // 初始大小为2，避免过度分配
    std::vector<int> factors = {2, 3, 5};
    buffer[1] = UGLYNUM_YES; // 1 是第一个丑数
    int pos = 1; // 初始位置为1，因为1是第一个丑数
    return nthUglyNumberSolve(n, pos, buffer, factors, 2);
}

//--------------------       Chat GPT    ------------------------------
#define UGLYNUM_YES 1
#define UGLYNUM_NO 0
#define UGLYNUM_UNDEFINE -1

int nthUglyNumber(int n) {
    if (n <= 0) return 0;
    std::vector<int> buffer(n);
    buffer[0] = 1; // 第一个丑数是1
    int pos2 = 0, pos3 = 0, pos5 = 0;
    for (int i = 1; i < n; ++i) {
        buffer[i] = std::min({buffer[pos2] * 2, buffer[pos3] * 3, buffer[pos5] * 5});  // 用的很妙，用上了贪心
        if (buffer[i] == buffer[pos2] * 2) ++pos2;
        if (buffer[i] == buffer[pos3] * 3) ++pos3;
        if (buffer[i] == buffer[pos5] * 5) ++pos5;
    }
    return buffer[n - 1];
}


//--------------------------------   左神--
// 丑数 II
// 给你一个整数 n ，请你找出并返回第 n 个 丑数
// 丑数 就是只包含质因数 2、3 或 5 的正整数
// 测试链接 : https://leetcode.cn/problems/ugly-number-ii/
public class Code05_UglyNumberII {

	// 时间复杂度O(n)，n代表第n个丑数
	public static int nthUglyNumber(int n) {
		// dp 0 1 2 ...  n
		//      1 2 ...  ?
		int[] dp = new int[n + 1];
		dp[1] = 1;
		for (int i = 2, i2 = 1, i3 = 1, i5 = 1, a, b, c, cur; i <= n; i++) {
			a = dp[i2] * 2;
			b = dp[i3] * 3;
			c = dp[i5] * 5;
			cur = Math.min(Math.min(a, b), c);
			if (cur == a) {
				i2++;
			}
			if (cur == b) {
				i3++;
			}
			if (cur == c) {
				i5++;
			}
			dp[i] = cur;
		}
		return dp[n];
	}

}




