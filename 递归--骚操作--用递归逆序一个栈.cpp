


/*
目的就是 不用别的大空间了，就在这个栈空间上修改

而这个题的 解题关键 就是 通过 递归保存弹出元素这个值
*/
int bottomOut(vector<int>& arr)
{
    int top = arr.back();
    arr.pop_back(); //这个题要求的 这个栈 内容不为空

    if (arr.empty())
    {
        return top;
    }else{
        int ans = bottomOut(arr);
        arr.push_back(top);
        return ans;
    }
}


//----------------------------左神

// 用递归函数逆序栈
public class Code05_ReverseStackWithRecursive {

	public static void reverse(Stack<Integer> stack) {
		if (stack.isEmpty()) {
			return;
		}
		int num = bottomOut(stack);
		reverse(stack);
		stack.push(num);
	}

	// 栈底元素移除掉，上面的元素盖下来
	// 返回移除掉的栈底元素
	public static int bottomOut(Stack<Integer> stack) {
		int ans = stack.pop();
		if (stack.isEmpty()) {
			return ans;
		} else {
			int last = bottomOut(stack);
			stack.push(ans);
			return last;
		}
	}

	public static void main(String[] args) {
		Stack<Integer> stack = new Stack<Integer>();
		stack.push(1);
		stack.push(2);
		stack.push(3);
		stack.push(4);
		stack.push(5);
		reverse(stack);
		while (!stack.isEmpty()) {
			System.out.println(stack.pop());
		}
	}

}

