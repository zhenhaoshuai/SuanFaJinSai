/*
这个 可以用嵌套 和 并列 
动态规划

这个算法 是 manacher（马拉车算法）Manacher算法主要是处理字符串中关于回文串的问题的，它可以在 O（n） 的时间处理出以字符串中每一个字符为中心的回文串半径，由于将原字符串处理成两倍长度的新串

(  )  )  (  )  (  )  (  (  )
0  1  2  3  4  5  6  7  8  9    子串一定要以 i 位置结尾，它往左延伸 多长的部分 能整体都是 有效串，我们把每个答案都算出来，最后答案就出来了
从0位置 ( 往左推 都是无效的 所以 有效长度 是 0 ---  所以遇到左括号 答案为 0 
0 
从1位置 往左 为 2
0  2 
从2 位置，往左推 多远 有效，单独不行必须成对 为 0
0  2  0
从 3 位置上，以 ( 往左 为 0
0  2  0  0
从 4 位置上
0  2  0  0  2
从 5 位置上
0  2  0  0  2  0
从 6 位置上
0  2  0  0  2  0  4
7：
0  2  0  0  2  0  4  0
8：
0  2  0  0  2  0  4  0  0
9：
0  2  0  0  2  0  4  0  0  2

所以 答案 就是  每个位置上 最大的那个
所以 我们 dp[i] 的 含义就出来了，i 位置 最多走多远

      |-  1). [i]->(,dp[i] = 0
dp[i] |                                                  |- a). [p] = ) dp[i] = 0
      |_  2). [i]->),根据dp[i-1]的长度往前跳到匹配的 P位置    |
                                                         |- b). [p] = (, dp[i] = dp[i-1] + 2 + dp[p-1] 这句话的意思就是 dp[i-1] + 2 就是 （。。。）+ 2,原来 dp[i-1]的答案 这对 和里面 ...<-(...) p位置往前的答案


(  (  )  (  )  )  (  )  )  (  )  (  )  (  )  (  (  )  )
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18

所以 像这样的 阴阳 2个符号 进行匹配，我们就可以用 这个 来实现
*/

int longestValidParentheses(string s) {
    vector<int> dp(s.size()+1, 0);
    
    dp[0] = 0;
    int pos = 1;
    int max = 0;
    while (pos <= s.size())
    {
        if ('(' == s[pos])
        {
            dp[pos] = 0;
        }else if (')' == s[pos])
        { // 开始往前开始找对应的括号
            if ((pos - dp[pos - 1] - 1 >= 0) && ('(' == s[pos - dp[pos - 1] - 1])) // 我们根据前一个值 可以跳过 值 直接去对应的位置判断
            {
                // dp[i] = dp[i-1] + 2 + dp[p-1] 这句话的意思就是 dp[i-1] + 2 就是 （。。。）+ 2,原来 dp[i-1]的答案 这对 和里面 ...<-(...) p位置往前的答案
                if ((pos - dp[pos - 1]) >= 2) // 就是 0 1 2 的位置要空3个位置 避免 这样的问题 ()())
                {
                    dp[pos] = dp[pos - 1] + 2 + dp[pos-dp[pos-1] - 1 - 1];
                }else{
                    dp[pos] = dp[pos - 1] + 2;
                }
            }else{
                dp[pos] = 0;
            }
        }
        max = std::max(max,dp[pos]);
        ++pos;
    }
    return max;
}


//------------------------------Ghay GPT---
int longestValidParentheses(std::string s) {
    std::vector<int> dp(s.size(), 0);  // 初始化 dp 数组，长度为字符串长度，初始值为 0
    int max_len = 0;  // 用于存储最长有效括号的长度
    
    for (int pos = 1; pos < s.size(); ++pos) {  // 从位置 1 开始遍历字符串
        if (s[pos] == ')') {  // 只在当前字符为 ')' 时进行处理
            if (s[pos - 1] == '(') {  // 检查前一个字符是否是 '('
                dp[pos] = (pos >= 2 ? dp[pos - 2] : 0) + 2;  // 直接更新 dp[pos]，并加上前面的有效长度
            } else if (pos - dp[pos - 1] > 0 && s[pos - dp[pos - 1] - 1] == '(') {  // 检查匹配的 '('
                dp[pos] = dp[pos - 1] + ((pos - dp[pos - 1]) >= 2 ? dp[pos - dp[pos - 1] - 2] : 0) + 2;
            }
            max_len = std::max(max_len, dp[pos]);  // 更新最大长度
        }
    }

    return max_len;
}


//----------------------------------  左神 --
// 最长有效括号
// 给你一个只包含 '(' 和 ')' 的字符串
// 找出最长有效（格式正确且连续）括号子串的长度。
// 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/
public class Code06_LongestValidParentheses {

	// 时间复杂度O(n)，n是str字符串的长度
	public static int longestValidParentheses(String str) {
		char[] s = str.toCharArray();
		// dp[0...n-1]
		// dp[i] : 子串必须以i位置的字符结尾的情况下，往左整体有效的最大长度
		int[] dp = new int[s.length];
		int ans = 0;
		for (int i = 1, p; i < s.length; i++) {
			if (s[i] == ')') {
				p = i - dp[i - 1] - 1;
				//  ?         )
				//  p         i
				if (p >= 0 && s[p] == '(') {
					dp[i] = dp[i - 1] + 2 + (p - 1 >= 0 ? dp[p - 1] : 0);
				}
			}
			ans = Math.max(ans, dp[i]);
		}
		return ans;
	}

}


