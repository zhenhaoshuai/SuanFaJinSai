public class Code01_QuickSort {

	public static int MAXN = 100001;

	public static int[] arr = new int[MAXN];

	public static int n;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StreamTokenizer in = new StreamTokenizer(br);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		in.nextToken();
		n = (int) in.nval;
		for (int i = 0; i < n; i++) {
			in.nextToken();
			arr[i] = (int) in.nval;
		}
		quickSort2(0, n - 1);
		for (int i = 0; i < n - 1; i++) {
			out.print(arr[i] + " ");
		}
		out.println(arr[n - 1]);
		out.flush();
		out.close();
		br.close();
	}

	// 随机快速排序经典版(不推荐)
	// 甚至在洛谷上测试因为递归开太多层会爆栈导致出错
	public static void quickSort1(int l, int r) {
		// l == r，只有一个数
		// l > r，范围不存在，不用管
		if (l >= r) {
			return;
		}
		// 随机这一下，常数时间比较大
		// 但只有这一下随机，才能在概率上把快速排序的时间复杂度收敛到O(n * logn)
		// l......r 随机选一个位置，x这个值，做划分
		int x = arr[l + (int) (Math.random() * (r - l + 1))];
		int mid = partition1(l, r, x);
		quickSort1(l, mid - 1);
		quickSort1(mid + 1, r);
	}

	// 已知arr[l....r]范围上一定有x这个值
	// 划分数组 <=x放左边，>x放右边
	// 并且确保划分完成后<=x区域的最后一个数字是x
	public static int partition1(int l, int r, int x) {
		// a : arr[l....a-1]范围是<=x的区域
		// xi : 记录在<=x的区域上任何一个x的位置，哪一个都可以
		int a = l, xi = 0;
		for (int i = l; i <= r; i++) {
			if (arr[i] <= x) {
				swap(a, i);
				if (arr[a] == x) {
					xi = a;
				}
				a++;
			}
		}
		swap(xi, a - 1);
		return a - 1;
	}

	public static void swap(int i, int j) {
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}

	// 随机快速排序改进版(推荐)
	// 可以通过所有测试用例
	public static void quickSort2(int l, int r) {
		if (l >= r) {
			return;
		}
		// 随机这一下，常数时间比较大
		// 但只有这一下随机，才能在概率上把快速排序的时间复杂度收敛到O(n * logn)
		int x = arr[l + (int) (Math.random() * (r - l + 1))];
		partition2(l, r, x);
		// 为了防止底层的递归过程覆盖全局变量
		// 这里用临时变量记录first、last
		int left = first;
		int right = last;
		quickSort2(l, left - 1);
		quickSort2(right + 1, r);
	}

	// 荷兰国旗问题
	public static int first, last;

	// 已知arr[l....r]范围上一定有x这个值
	// 划分数组 <x放左边，==x放中间，>x放右边
	// 把全局变量first, last，更新成==x区域的左右边界
	public static void partition2(int l, int r, int x) {
		first = l;
		last = r;
		int i = l;
		while (i <= last) {
			if (arr[i] == x) {
				i++;
			} else if (arr[i] < x) {
				swap(first++, i++);
			} else {
				swap(i, last--);
			}
		}
	}

}


//-----------------------------------------------------内容2------------------

// 随机快速排序，填函数练习风格
// 测试链接 : https://leetcode.cn/problems/sort-an-array/

public class Code02_QuickSort {

	public static int[] sortArray(int[] nums) {
		if (nums.length > 1) {
			quickSort2(nums, 0, nums.length - 1);
		}
		return nums;
	}

	// 随机快速排序经典版(不推荐)
	public static void quickSort1(int[] arr, int l, int r) {
		if (l >= r) {
			return;
		}
		// 随机这一下，常数时间比较大
		// 但只有这一下随机，才能在概率上把快速排序的时间复杂度收敛到O(n * logn)
		int x = arr[l + (int) (Math.random() * (r - l + 1))];
		int mid = partition1(arr, l, r, x);
		quickSort1(arr, l, mid - 1);
		quickSort1(arr, mid + 1, r);
	}

	// 已知arr[l....r]范围上一定有x这个值
	// 划分数组 <=x放左边，>x放右边，并且确保划分完成后<=x区域的最后一个数字是x
	public static int partition1(int[] arr, int l, int r, int x) {
		// a : arr[l....a-1]范围是<=x的区域
		// xi : 记录在<=x的区域上任何一个x的位置，哪一个都可以
		int a = l, xi = 0;
		for (int i = l; i <= r; i++) {
			if (arr[i] <= x) {
				swap(arr, a, i);
				if (arr[a] == x) {
					xi = a;
				}
				a++;
			}
		}
		swap(arr, xi, a - 1);
		return a - 1;
	}

	public static void swap(int[] arr, int i, int j) {
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}

	// 随机快速排序改进版(推荐)
	public static void quickSort2(int[] arr, int l, int r) {
		if (l >= r) {
			return;
		}
		// 随机这一下，常数时间比较大
		// 但只有这一下随机，才能在概率上把快速排序的时间复杂度收敛到O(n * logn)
		int x = arr[l + (int) (Math.random() * (r - l + 1))];
		partition2(arr, l, r, x);
		// 为了防止底层的递归过程覆盖全局变量
		// 这里用临时变量记录first、last
		int left = first;
		int right = last;
		quickSort2(arr, l, left - 1);
		quickSort2(arr, right + 1, r);
	}

	// 荷兰国旗问题
	public static int first, last;

	// 已知arr[l....r]范围上一定有x这个值
	// 划分数组 <x放左边，==x放中间，>x放右边
	// 把全局变量first, last，更新成==x区域的左右边界
	public static void partition2(int[] arr, int l, int r, int x) {
		first = l;
		last = r;
		int i = l;
		while (i <= last) {
			if (arr[i] == x) {
				i++;
			} else if (arr[i] < x) {
				swap(arr, first++, i++);
			} else {
				swap(arr, i, last--);
			}
		}
	}

}

