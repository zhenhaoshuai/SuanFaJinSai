/*
题目要求：
一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
示例 1：

输入：s = "12"
输出：2
解释：它可以解码为 "AB"（1 2）或者 "L"（12）。
示例 2：

输入：s = "226"
输出：3
解释：它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
示例 3：

输入：s = "06"
输出：0
解释："06" 无法映射到 "F" ，因为存在前导零（"6" 和 "06" 并不等价）。

组为  (1 11 06) ，因为 "06" 不能映射为 "F" ，这是由于 "6" 和 "06" 在映射中并不等价
题目数据保证答案肯定是一个 32位 的整数  ---- 所以 这么我们不需要是用 取模 的技巧
*/

#define ARRAY_LEN 100

/*  失败
// 我的思路 就是 ：
// 最小单位 - 最小单位 - 最小单位 - 最小单位 - 最小单位 
// 最小单位 - 最小单位 - 最小单位 - 最小单位 
// 最小单位 - 最小单位 - 最小单位
// 最小单位 - 最小单位 
// 最小单位 

// 缓存都是这样来取最小单位

// "AAJF" ，将消息分组为 (1 1 10 6) 这些组成了最小单位了
// "KJF" ，将消息分组为 (11 10 6)
// 这个就是 优化的地方就是 每次修改前面的 内容的时候，每次后面的内容 就可以利用上 动态规划--记忆化搜索，如 这里10 6 就可以优化掉这部分
// */
// void numDecodingsSolve(string& str,vector<int> buffer,int& pos,vector<char>& decodeStr) {

//     int val = 0;
//     for (int i = 0,j = 0; i < str.size(); i++)
//     {
//         if (0 == std::stoi(str[i])){
//             val = (val*10) + std::stoi(str[i]);
//         }else{
//             val = std::stoi(str[i]);
//         }
//         buffer[j] =  val;
//         if (0 != std::stoi(str[i])){
//             ++j;
//             val = 0;
//         }
//     } // 全部转换到缓存中去 //一个长度的

//     for (int i = 2; i < 3; i++) // 改题要求的是 26以内 所以是 2位数
//     {
        
//     }
    
        
    
// }


/*
---------------又学到一招 -- 就是利用 2个执行流程上的顺序递归，同时 跨的长度不一样 实现 需求

--
    --
        --
            --
                --
                |
            |
        |
    |
|

3. 处理有效字符
java
Copy code
else {
    ans = f1(s, i + 1);
    if (i + 1 < s.length && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
        ans += f1(s, i + 2);
    }
}
如果当前字符不是 '0'，首先递归调用 f1(s, i + 1) 计算单个字符的解码方案。

然后，检查当前字符和下一个字符组成的两位数是否在 1 到 26 之间。如果是，则递归调用 f1(s, i + 2) 计算两位数的解码方案，并将结果加到 ans 中。

示例分析
假设字符串 s 是 "226"：

f1(['2', '2', '6'], 0) 会递归调用 f1(['2', '2', '6'], 1) 和 f1(['2', '2', '6'], 2)。
f1(['2', '2', '6'], 1) 会递归调用 f1(['2', '2', '6'], 2) 和 f1(['2', '2', '6'], 3)。
f1(['2', '2', '6'], 2) 只会递归调用 f1(['2', '2', '6'], 3)。
f1(['2', '2', '6'], 3) 返回 1，因为已经处理完所有字符。
计算步骤如下：

f1(['2', '2', '6'], 2) 返回 1。
f1(['2', '2', '6'], 1) 返回 1 + 1 = 2。
f1(['2', '2', '6'], 0) 返回 2 + 1 = 3。
所以，字符串 "226" 有 3 种解码方式："BBF"、"VF" 和 "BZ"。

总结
这段代码利用递归的方法，逐步检查字符串中每个字符及其可能的两位组合，从而计算出所有可能的有效解码方案。每次递归调用都缩小了问题规模，直到处理完所有字符或遇到无法解码的字符为止
*/

int numDecodingsSolve(string& str,int pos) {
    int ans;
    if (str.size() == pos) {
        return 1;
    }

    if (str[pos] == '0')
    {
        ans = 0;//这个位置 为0 ，我们 第一次递归进入第二个递归时回退的时候，发现这个位置等于0所以，这次就不能计入，因为不符合规则
    }else{
        ans = numDecodingsSolve(str,pos + 1); // 因为这个题 123 中 只有 12 位 可以组成 满足条件的，所以我们以后 有更多位置时，我们就可以用个 for 来
        if (pos + 1 < str.size()) {
            int twoDigit = (str[pos] - '0') * 10 + (str[pos + 1] - '0');
            if (twoDigit >= 10 && twoDigit <= 26) {
                ans += numDecodingsSolve(str, pos + 2); // 双字符解码
            }
        }
    }
    
    return ans;
}

int numDecodings(string s) {
    string str(s);
    return numDecodingsSolve(str,0);
}


//-------------------------------下面使用 动态规划，记忆化搜索--来给上面超时的  递归  剪枝
int numDecodingsSolve(string& str,vector<int>& bufferFlg,int pos) {
    int ans;
    if (str.size() == pos) {
        return 1;
    }
    if (-1 != bufferFlg[pos])
    {
        return bufferFlg[pos]; //这样将 再次 过来的进行 关闭掉
    }

    if (str[pos] == '0')
    {
        ans = 0;//这个位置 为0 ，我们 第一次递归进入第二个递归时回退的时候，发现这个位置等于0所以，这次就不能计入，因为不符合规则
    }else{
        ans = numDecodingsSolve(str,bufferFlg,pos + 1); // 因为这个题 123 中 只有 12 位 可以组成 满足条件的，所以我们以后 有更多位置时，我们就可以用个 for 来
        if (pos + 1 < str.size()) {
            int twoDigit = (str[pos] - '0') * 10 + (str[pos + 1] - '0');
            if (twoDigit >= 10 && twoDigit <= 26) {
                ans += numDecodingsSolve(str,bufferFlg, pos + 2); // 双字符解码
            }
        }
    }
    bufferFlg[pos] = ans;//表示这个已经传递过了
    return ans;
}




int numDecodings(string s) {
    string str(s);
    vector<int> buffer(ARRAY_LEN ,-1);
    return numDecodingsSolve(str,buffer,0);
}

//-------------------左神---

// 解码方法
// 一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
// 要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）
// 例如，"11106" 可以映射为："AAJF"、"KJF"
// 注意，消息不能分组为(1 11 06)，因为 "06" 不能映射为 "F"
// 这是由于 "6" 和 "06" 在映射中并不等价
// 给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数
// 题目数据保证答案肯定是一个 32位 的整数
// 测试链接 : https://leetcode.cn/problems/decode-ways/
public class Code03_DecodeWays {

	// 暴力尝试
	public static int numDecodings1(String s) {
		return f1(s.toCharArray(), 0);
	}

	// s : 数字字符串 
	// s[i....]有多少种有效的转化方案
	public static int f1(char[] s, int i) {
		if (i == s.length) {
			return 1;
		}
		int ans;
		if (s[i] == '0') {
			ans = 0;
		} else {
			ans = f1(s, i + 1);
			if (i + 1 < s.length && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
				ans += f1(s, i + 2);
			}
		}
		return ans;
	}

	// 暴力尝试改记忆化搜索
	public static int numDecodings2(String s) {
		int[] dp = new int[s.length()];
		Arrays.fill(dp, -1);
		return f2(s.toCharArray(), 0, dp);
	}

	public static int f2(char[] s, int i, int[] dp) {
		if (i == s.length) {
			return 1;
		}
		if (dp[i] != -1) {
			return dp[i];
		}
		int ans;
		if (s[i] == '0') {
			ans = 0;
		} else {
			ans = f2(s, i + 1, dp);
			if (i + 1 < s.length && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
				ans += f2(s, i + 2, dp);
			}
		}
		dp[i] = ans;
		return ans;
	}

	// 严格位置依赖的动态规划
	public static int numDecodings3(String str) {
		char[] s = str.toCharArray();
		int n = s.length;
		int[] dp = new int[n + 1];
		dp[n] = 1;
		for (int i = n - 1; i >= 0; i--) {
			if (s[i] == '0') {
				dp[i] = 0;
			} else {
				dp[i] = dp[i + 1];
				if (i + 1 < s.length && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
					dp[i] += dp[i + 2];
				}
			}
		}
		return dp[0];
	}

	// 严格位置依赖的动态规划 + 空间压缩
	public static int numDecodings4(String s) {
		// dp[i+1]
		int next = 1;
		// dp[i+2]
		int nextNext = 0;
		for (int i = s.length() - 1, cur; i >= 0; i--) {
			if (s.charAt(i) == '0') {
				cur = 0;
			} else {
				cur = next;
				if (i + 1 < s.length() && ((s.charAt(i) - '0') * 10 + s.charAt(i + 1) - '0') <= 26) {
					cur += nextNext;
				}
			}
			nextNext = next;
			next = cur;
		}
		return next;
	}

}

