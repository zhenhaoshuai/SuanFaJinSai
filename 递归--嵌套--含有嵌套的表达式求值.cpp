/*
题目给的都是正确的表达式

基本问题：
30 + 16 - 4 + 3 * 2 / 2 * 4
12 3 45 6 7 8 ....   这样每个字符串都编号


使用2个栈 数字栈 和 符号栈 
cur = cur * 10 + 'cur'-'0'//这里收集数字

当遇到* / 的时候就先算了再放入栈
数字栈：30 16 4 12
符号栈：+  -  +  +

有括号的问题：

36 - （ 4 * （ 3 + 2 * （ 1 - 6 ） + 5 ） + 17
01 2  3 4 5  6 7 。。。。。。

因为这个括号是一个整体，当我们计算完括号内的，外面的步骤我们就出去 就跳过这括号的内容 而是使用括号的结果 where_pos

f(0):
数字栈：36
操作栈：+
  f(4): 因为遇到了(,(后一个才是内容，所以我们使用 f(4)
  数字栈：4
  操作栈：*
    f(7):
    数字栈：3 2
    操作栈：+ *
where_pos所以where_pos 这个变量可以用在退出时，给上一层知道计算到哪个位置了
    
*/

int calculateSolve(string& str,int& where_pos)
{
    vector<int> nums_stack; //数值栈
    vector<char> operation_stack; //操作栈
    int num = 0;//就是从str进行取数
    while (where_pos < str.size())
    {
        if (isdigit(str[where_pos]))
        {
            num = (num * 10) + (str[where_pos] - '0'); //从字符串中取数
            ++where_pos;
        }else if (('+' == str[where_pos]) || ('-' == str[where_pos]) || ('*' == str[where_pos]) || ('/' == str[where_pos])){
            if ((!operation_stack.empty()) && ('*' == operation_stack.back()) || ('/' == operation_stack.back())) //这里 对这种有优先级的处理了，下面全部进行求结果是就不用考虑优先级了
            {
                int temp = nums_stack.back();
                nums_stack.pop_back();

                if (('*' == operation_stack.back()))
                {
                    nums_stack.push_back(temp * num);
                }else{ //"/"
                    nums_stack.push_back(temp / num);
                }
                operation_stack.pop_back();
                
            }else{
                nums_stack.push_back(num); //压入数值
            }
            num = 0; //数值复原
            
            operation_stack.push_back(str[where_pos]); //压入操作
            ++where_pos;
            

        }else if ('(' == str[where_pos]){
            ++where_pos;
            num = calculateSolve(str,where_pos);//由于整体返回的值 会 放入num
        }else if (')' == str[where_pos]){
            nums_stack.push_back(num); //压入数值
            num = 0; //数值复原
            ++where_pos;
            break; //遇到一个 ） 说明这次嵌套结束
        }else{
            ++where_pos;//表示遇到了别的字符 如空格
        }
    }
    
    //计算数据
    int result = 0;
    if (!nums_stack.empty())
    {
        char operation;
        int val = 0;
        result = nums_stack.back();
        nums_stack.pop_back(); //因为这个栈中这个num 总是比 operation 多1个
        while (!nums_stack.empty)
        {
            operation = operation_stack.back();
            operation_stack.pop_back();
            val = nums_stack.back();
            nums_stack.pop_back();
            if ('+' == operation)
            {
                result += val; 
            }else{
                result -= val; 
            }
        }
    }
    
    return result;
}

int calculate(string str)
{
    int result = 0;
   int where_pos = 0;
   result = calculateSolve(str,where_pos);
   return result;
}




// -----------------------------Chatp GPT---------
int calculateSolve(string& str, int& where_pos) {
    vector<int> nums_stack; // 数值栈
    vector<char> operation_stack; // 操作栈
    int num = 0; // 从 str 中取数

    while (where_pos < str.size()) {
        if (isdigit(str[where_pos])) {
            num = (num * 10) + (str[where_pos] - '0'); // 从字符串中取数
            ++where_pos;
        } else if (str[where_pos] == '+' || str[where_pos] == '-' || str[where_pos] == '*' || str[where_pos] == '/') {
            if (!operation_stack.empty() && (operation_stack.back() == '*' || operation_stack.back() == '/')) {
                int temp = nums_stack.back();
                nums_stack.pop_back();

                if (operation_stack.back() == '*') {
                    nums_stack.push_back(temp * num);
                } else { // '/'
                    nums_stack.push_back(temp / num);
                }
                operation_stack.pop_back();
            } else {
                nums_stack.push_back(num); // 压入数值
            }
            num = 0; // 数值复原
            operation_stack.push_back(str[where_pos]); // 压入操作
            ++where_pos;

        } else if (str[where_pos] == '(') {
            ++where_pos; // 跳过 '('
            num = calculateSolve(str, where_pos); // 递归处理括号内的表达式
        } else if (str[where_pos] == ')') {
            nums_stack.push_back(num); // 压入数值
            num = 0; // 数值复原
            ++where_pos;
            break; // 遇到 ')'，嵌套结束
        } else {
            ++where_pos; // 跳过空格等其他字符
        }
    }

    nums_stack.push_back(num); // 压入最后一个数值

    // 计算数据
    int result = nums_stack[0]; // 初始化结果为第一个数值
    for (size_t i = 0; i < operation_stack.size(); ++i) {
        char operation = operation_stack[i];
        int val = nums_stack[i + 1];
        if (operation == '+') {
            result += val;
        } else {
            result -= val;
        }
    }

    return result;
}


//-----------------------------左神
// 含有嵌套的表达式求值
// 测试链接 : https://leetcode.cn/problems/basic-calculator-iii/
public class Code01_BasicCalculatorIII {

	public static int calculate(String str) {
		where = 0;
		return f(str.toCharArray(), 0);
	}

	public static int where;

	// s[i....]开始计算，遇到字符串终止 或者 遇到)停止
	// 返回 : 自己负责的这一段，计算的结果
	// 返回之间，更新全局变量where，为了上游函数知道从哪继续！
	public static int f(char[] s, int i) {
		int cur = 0;
		ArrayList<Integer> numbers = new ArrayList<>();
		ArrayList<Character> ops = new ArrayList<>();
		while (i < s.length && s[i] != ')') {
			if (s[i] >= '0' && s[i] <= '9') {
				cur = cur * 10 + s[i++] - '0';
			} else if (s[i] != '(') {
				// 遇到了运算符 + - * /
				push(numbers, ops, cur, s[i++]);
				cur = 0;
			} else {
				// i (.....)
				// 遇到了左括号！
				cur = f(s, i + 1);
				i = where + 1;
			}
		}
		push(numbers, ops, cur, '+');
		where = i;
		return compute(numbers, ops);
	}

	public static void push(ArrayList<Integer> numbers, ArrayList<Character> ops, int cur, char op) {
		int n = numbers.size();
		if (n == 0 || ops.get(n - 1) == '+' || ops.get(n - 1) == '-') {
			numbers.add(cur);
			ops.add(op);
		} else {
			int topNumber = numbers.get(n - 1);
			char topOp = ops.get(n - 1);
			if (topOp == '*') {
				numbers.set(n - 1, topNumber * cur);
			} else {
				numbers.set(n - 1, topNumber / cur);
			}
			ops.set(n - 1, op);
		}
	}

	public static int compute(ArrayList<Integer> numbers, ArrayList<Character> ops) {
		int n = numbers.size();
		int ans = numbers.get(0);
		for (int i = 1; i < n; i++) {
			ans += ops.get(i - 1) == '+' ? numbers.get(i) : -numbers.get(i);
		}
		return ans;
	}

}


