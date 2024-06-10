/*
给定一个字符串 s，计算 s 的 不同非空子序列 的个数。因为结果可能很大，所以返回答案需要对 10^9 + 7 取余 。

字符串的 子序列 是经由原字符串删除一些（也可能不删除）字符但不改变剩余字符相对位置的一个新字符串。

例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是。
 

示例 1：

输入：s = "abc"
输出：7
解释：7 个不同的子序列分别是 "a", "b", "c", "ab", "ac", "bc", 以及 "abc"。
示例 2：

输入：s = "aba"
输出：6
解释：6 个不同的子序列分别是 "a", "b", "ab", "ba", "aa" 以及 "aba"。
示例 3：

输入：s = "aaa"
输出：3
解释：3 个不同的子序列分别是 "a", "aa" 以及 "aaa"。

*/

/*
公式： 纯新 = all - 当前字符上次记录，当前字符记录 += 纯新， all += 纯新
解过程：
a b a a b ...
{}
0:{} {a}
1:{} {a} {b} {ab}
2:遇到重复的了，就将a的都把前面作为单位 都 加个 a  ..{} {a} {b} {ab} {a}(x) ,{aa} {ba} {aba}

*/




//------------------左神

// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，所以返回答案需要对 10^9 + 7 取余
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/
public class Code08_DistinctSubsequencesII {

	// 时间复杂度O(n)，n是字符串s的长度
	public static int distinctSubseqII(String s) {
		int mod = 1000000007;
		char[] str = s.toCharArray();
		int[] cnt = new int[26];
		int all = 1, newAdd;
		for (char x : str) {
			newAdd = (all - cnt[x - 'a'] + mod) % mod;
			cnt[x - 'a'] = (cnt[x - 'a'] + newAdd) % mod;
			all = (all + newAdd) % mod;
		}
		return (all - 1 + mod) % mod;
	}

}
