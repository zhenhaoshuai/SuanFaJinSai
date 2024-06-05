// 示例 1：

// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"
// 示例 2：

// 输入：s = "3[a2[c]]"
// 输出："accaccacc"
// 示例 3：

// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"
// 示例 4：

// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"

string decodeStringSolve(string& str, int& pos) {
    vector<string> content_stack; // 内容stack
    vector<int> content_count;    // 内容数量

    int num = 0;
    string strTemp;

    while (pos < str.size()) {
        if (isdigit(str[pos])) {
            if (!strTemp.empty()) {
                content_stack.push_back(strTemp);
                content_count.push_back(1); // 记为 1 次---这样所有的内容都只 记录了一次
                strTemp.clear();
            }
            
            num = (num * 10) + (str[pos] - '0');
            ++pos;
        } else if ('[' == str[pos]) {
            ++pos;
            string nested = decodeStringSolve(str, pos);
            for (int i = 0; i < num; ++i) {  //这里把所有的内容都放到一起去
                strTemp += nested;
            }
            num = 0; // 重置 num
        } else if (isalpha(str[pos])) {
            strTemp += str[pos];
            ++pos;
        } else if (']' == str[pos]) {
            ++pos;
            break;
        } else {
            ++pos; // 跳过未知的字符，如空格
        }
    }

    // 处理字符串
    while (!content_stack.empty()) {
        strTemp = content_stack.back() + strTemp;
        content_stack.pop_back();
    }

    return strTemp;
}

string decodeString(string s) {
    int pos = 0;
    return decodeStringSolve(s, pos);
}


//----------------------------------左神
// 含有嵌套的字符串解码
// 测试链接 : https://leetcode.cn/problems/decode-string/
public class Code02_DecodeString {

	public static String decodeString(String str) {
		where = 0;
		return f(str.toCharArray(), 0);
	}

	public static int where;

	// s[i....]开始计算，遇到字符串终止 或者 遇到 ] 停止
	// 返回 : 自己负责的这一段字符串的结果
	// 返回之间，更新全局变量where，为了上游函数知道从哪继续！
	public static String f(char[] s, int i) {
		StringBuilder path = new StringBuilder();
		int cnt = 0;
		while (i < s.length && s[i] != ']') {
			if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
				path.append(s[i++]);
			} else if (s[i] >= '0' && s[i] <= '9') {
				cnt = cnt * 10 + s[i++] - '0';
			} else {
				// 遇到 [ 
				// cnt = 7 * ? 
				path.append(get(cnt, f(s, i + 1)));
				i = where + 1;
				cnt = 0;
			}
		}
		where = i;
		return path.toString();
	}

	public static String get(int cnt, String str) {
		StringBuilder builder = new StringBuilder();
		for (int i = 0; i < cnt; i++) {
			builder.append(str);
		}
		return builder.toString();
	}

}


