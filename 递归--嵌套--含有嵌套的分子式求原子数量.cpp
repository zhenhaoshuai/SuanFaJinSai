
// 示例 1：

// 输入：formula = "H2O"
// 输出："H2O"
// 解释：原子的数量是 {'H': 2, 'O': 1}。
// 示例 2：

// 输入：formula = "Mg(OH)2"
// 输出："H2MgO2"
// 解释：原子的数量是 {'H': 2, 'Mg': 1, 'O': 2}。
// 示例 3：

// 输入：formula = "K4(ON(SO3)2)2"
// 输出："K4N2O14S4"
// 解释：原子的数量是 {'K': 4, 'N': 2, 'O': 14, 'S': 4}。

// 含有嵌套的分子式求原子数量
// 测试链接 : https://leetcode.cn/problems/number-of-atoms/

/*
还是用的那个 递归 嵌套的 套路
这里就是把 A2B3C4  这样带括号的看成一个整体，然后就是 (ABC)2 看成 一体
*/
map<string, int> countOfAtomsSolve(string &formula, int &pos) {
    map<string, int> result; // first : 元素内容, second : 元素个数
    string strTemp;
    int num = 0;

    while (pos < formula.size()) {
        if (isalpha(formula[pos])) {
            if ((!strTemp.empty()) && (isupper(formula[pos]))) { //针对 KN这种情况 和 K4N 这种4的情况
                num = (num != 0) ? num : 1;
                result[strTemp] += num; //没有显式地初始化 result[strTemp]，它也会被默认初始化，然后执行加法操作
                strTemp = "";
                num = 0;
            }
            strTemp += formula[pos];
            ++pos;
        } else if (isdigit(formula[pos])) {
            num = (num * 10) + (formula[pos] - '0');
            ++pos;
        } else if ('(' == formula[pos]) {
            if (!strTemp.empty()) {  //针对 K4N2(  K4N(  , (  这种4的情况
                num = (num != 0) ? num : 1;
                result[strTemp] += num;
                strTemp = "";
                num = 0;
            }
            ++pos; // move to next character after '('
            map<string, int> resultTemp = countOfAtomsSolve(formula, pos);  //结算时刻，把嵌套内的东西要 和 当前层的内容要合并
            int multiplier = 1;
            int numTemp = 0;
            while (pos < formula.size() && isdigit(formula[pos])) { // 这里在一直使用去判断它内容 所有字符串
                numTemp = (numTemp * 10) + (formula[pos] - '0');
                ++pos;
            }
            multiplier = (numTemp != 0) ? numTemp : 1;
            for (auto &i : resultTemp) {
                result[i.first] += i.second * multiplier;
            }
        } else if (')' == formula[pos]) {
            ++pos;
            if (!strTemp.empty()) {
                num = (num != 0) ? num : 1;
                result[strTemp] += num;
                strTemp = "";
                num = 0;
            }
            return result; //遇到结束的时候，我们将这些返回
        } else {
            ++pos; // skip unknown characters like spaces
        }
    }

    if (!strTemp.empty()) {
        num = (num != 0) ? num : 1;
        result[strTemp] += num;
    }

    return result;
}

string countOfAtoms(string formula) {
    int pos = 0;
    map<string, int> resultMap = countOfAtomsSolve(formula, pos);

    // Convert map to vector and sort by element name
    vector<pair<string, int>> sortedResult(resultMap.begin(), resultMap.end());
    sort(sortedResult.begin(), sortedResult.end());

    // Construct the result string
    string resultStr;
    for (const auto &i : sortedResult) {
        resultStr += i.first;
        if (i.second > 1) {
            resultStr += to_string(i.second);
        }
    }

    return resultStr;
}


//----------------------------------------Chat GPT--
map<string, int> countOfAtomsSolve(string &formula, int &pos) {
    map<string, int> result;
    while (pos < formula.size()) {
        if (formula[pos] == '(') {
            ++pos;
            map<string, int> subResult = countOfAtomsSolve(formula, pos);
            int multiplier = 0;
            while (pos < formula.size() && isdigit(formula[pos])) {  // 这里用了一直去一个有数的位置来找值
                multiplier = multiplier * 10 + (formula[pos] - '0');
                ++pos;
            }
            multiplier = (multiplier == 0) ? 1 : multiplier;
            for (auto &elem : subResult) {
                result[elem.first] += elem.second * multiplier;
            }
        } else if (formula[pos] == ')') {
            ++pos;
            return result;
        } else {
            string element;
            element += formula[pos++];
            while (pos < formula.size() && islower(formula[pos])) {
                element += formula[pos++];
            }
            int count = 0;
            while (pos < formula.size() && isdigit(formula[pos])) {
                count = count * 10 + (formula[pos] - '0');
                ++pos;
            }
            count = (count == 0) ? 1 : count;
            result[element] += count; //一直在持续更新它
        }
    }
    return result;
}

string countOfAtoms(string formula) {
    int pos = 0;
    map<string, int> resultMap = countOfAtomsSolve(formula, pos);

    // Convert map to vector and sort by element name
    vector<pair<string, int>> sortedResult(resultMap.begin(), resultMap.end());
    sort(sortedResult.begin(), sortedResult.end());

    // Construct the result string
    string resultStr;
    for (const auto &elem : sortedResult) {
        resultStr += elem.first;
        if (elem.second > 1) {
            resultStr += to_string(elem.second);
        }
    }

    return resultStr;
}

//-----------------------------------------------左神
public class Code03_NumberOfAtoms {

	public static String countOfAtoms(String str) {
		where = 0;
		TreeMap<String, Integer> map = f(str.toCharArray(), 0);
		StringBuilder ans = new StringBuilder();
		for (String key : map.keySet()) {
			ans.append(key);
			int cnt = map.get(key);
			if (cnt > 1) {
				ans.append(cnt);
			}
		}
		return ans.toString();
	}

	public static int where;

	// s[i....]开始计算，遇到字符串终止 或者 遇到 ) 停止
	// 返回 : 自己负责的这一段字符串的结果，有序表！
	// 返回之间，更新全局变量where，为了上游函数知道从哪继续！
	public static TreeMap<String, Integer> f(char[] s, int i) {
		// ans是总表
		TreeMap<String, Integer> ans = new TreeMap<>();
		// 之前收集到的名字，历史一部分
		StringBuilder name = new StringBuilder();
		// 之前收集到的有序表，历史一部分
		TreeMap<String, Integer> pre = null;
		// 历史翻几倍
		int cnt = 0;
		while (i < s.length && s[i] != ')') {
			if (s[i] >= 'A' && s[i] <= 'Z' || s[i] == '(') {
				fill(ans, name, pre, cnt);
				name.setLength(0);
				pre = null;
				cnt = 0;
				if (s[i] >= 'A' && s[i] <= 'Z') {
					name.append(s[i++]);
				} else {
					// 遇到 (
					pre = f(s, i + 1);
					i = where + 1;
				}
			} else if (s[i] >= 'a' && s[i] <= 'z') {
				name.append(s[i++]);
			} else {
				cnt = cnt * 10 + s[i++] - '0';
			}
		}
		fill(ans, name, pre, cnt);
		where = i;
		return ans;
	}

	public static void fill(TreeMap<String, Integer> ans, StringBuilder name, TreeMap<String, Integer> pre, int cnt) {
		if (name.length() > 0 || pre != null) {
			cnt = cnt == 0 ? 1 : cnt;
			if (name.length() > 0) {
				String key = name.toString();
				ans.put(key, ans.getOrDefault(key, 0) + cnt);
			} else {
				for (String key : pre.keySet()) {
					ans.put(key, ans.getOrDefault(key, 0) + pre.get(key) * cnt);
				}
			}
		}
	}

}



