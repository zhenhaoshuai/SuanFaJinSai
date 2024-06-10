// 环绕字符串中唯一的子字符串
// ------  他们 2个 式子 中都是 a-z 这样有顺序的
// 定义字符串 base 为一个 "abcdefghijklmnopqrstuvwxyz" 无限环绕的字符串
// 所以 base 看起来是这样的：
// "..zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd.."
// 给你一个字符串 s ，请你统计并返回 s 中有多少 不同非空子串 也在 base 中出现
// 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/
/*
示例 1：

输入：s = "a"
输出：1
解释：字符串 s 的子字符串 "a" 在 base 中出现。
示例 2：

输入：s = "cac"
输出：2
解释：字符串 s 有两个子字符串 ("a", "c") 在 base 中出现。
示例 3：

输入：s = "zab"
输出：6
解释：字符串 s 有六个子字符串 ("z", "a", "b", "za", "ab", and "zab") 在 base 中出现。

*/

/*
这题思路 很难想到， 像 这种 延伸 和 子集 之类的，我们可以添加有某一个字符 延伸的最大值

base 串 ："abcdefghijklmnopqrstuvwxyz"
S : zabpxyzab
在  S 中 以 a做 结尾的子串，不管是什么子串，只要是 以 a做结尾的子串都算，请问有多少子串在 base 串中也是子串， 得去重
a 的 延伸的最大长度是 4长度， xyza ,就说明一定 它有 4个子串在 base串中 也是子串，分别是:  a ,因为这长度最长的 就一定包含了小的子串 za ,所以长度长的就一定会包含长度短的--这里要的是连续的
                                                                              za
                                                                             yza
                                                                            xyza
所以我只需要看 每个字符在 S 串中，它能在base串中能够延伸的最大长度，以'a'结尾在base中延伸的最大距离是 4 ，以 ‘b’ 字符在S中延伸，同时在base中也能延伸的最大长度是5， 所以最大距离就是用来去重的

z a b p x y z a b 
0 .. ........... 8
len  = 1, idx = 0 , z = 1
idx = 1, a 在base中连续的z是a的上一个,所以 len + 1 = 2, a = 2
同理 ++len = 3, b = 3
在p 时，由于p在base 中的上一个 不是 b ，所以 len = 1, p = 1
在x 时，由于x在base中的上一个 不是 p，所以 len = 1, x = 1
同理 ++len = 2,y = 2
同理 ++len = 3,z = 3
同理 ++len = 4,更新 a = 3 因为我们取最大值
同理 ++len = 5,更新 b = 5 因为我们取最大值
                                                                                
*/


//---------------------------------  左神

// 环绕字符串中唯一的子字符串
// 定义字符串 base 为一个 "abcdefghijklmnopqrstuvwxyz" 无限环绕的字符串
// 所以 base 看起来是这样的：
// "..zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd.."
// 给你一个字符串 s ，请你统计并返回 s 中有多少 不同非空子串 也在 base 中出现
// 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/
public class Code07_UniqueSubstringsWraparoundString {

	// 时间复杂度O(n)，n是字符串s的长度，字符串base长度为正无穷
	public static int findSubstringInWraproundString(String str) {
		int n = str.length();
		int[] s = new int[n];
		// abcde...z -> 0, 1, 2, 3, 4....25
		for (int i = 0; i < n; i++) {
			s[i] = str.charAt(i) - 'a';
		}
		// dp[0] : s中必须以'a'的子串，最大延伸长度是多少，延伸一定要跟据base串的规则
		int[] dp = new int[26];
		// s : c d e....
		//     2 3 4
		dp[s[0]] = 1;
		for (int i = 1, cur, pre, len = 1; i < n; i++) {
			cur = s[i];
			pre = s[i - 1];
			// pre cur
			if ((pre == 25 && cur == 0) || pre + 1 == cur) {
				// (前一个字符是'z' && 当前字符是'a') || 前一个字符比当前字符的ascii码少1
				len++;
			} else {
				len = 1;
			}
			dp[cur] = Math.max(dp[cur], len);
		}
		int ans = 0;
		for (int i = 0; i < 26; i++) {
			ans += dp[i];
		}
		return ans;
	}

}



