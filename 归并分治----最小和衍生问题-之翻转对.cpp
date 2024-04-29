#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>

const int N = 500;

int n = 0;

int datas[N]{0};
int aux_datas[N]{0};


//翻转对：
//给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
//
//你需要返回给定数组中的重要翻转对的数量。
//
//示例 1:
//
//输入: [1,3,2,3,1]
//输出: 2
//示例 2:
//
//输入: [2,4,3,5,1]
//输出: 3
//注意:
//
//给定数组的长度不会超过50000。
//输入数组中的所有数字都在32位整数的表示范围内。

//和上一道题 归并分治---小和问题是同一个问题 ，套模版出了答案
int merge(int L, int Mid, int R)
{
    int i = L, j = Mid + 1, t = 0;
    int sum = 0;//翻转对的个数
    while ((i <= Mid) && (j <= R)) {
        if (datas[i] > 2 * datas[j]) {
            sum++;
            //ChatGPT :sum += Mid - i + 1; // 如果 datas[i] > 2 * datas[j]，那么从 i 到 Mid 的所有元素都会满足条件
            j++;
        } else {
            i++;
        }
    }

    i = L, j = Mid + 1, t = 0;
    //下面是正常的归并排序
    while ((i <= Mid) && (j <= R)) {
        if (datas[i] > datas[j]) {
            aux_datas[t++] = datas[j++];
        } else {
            aux_datas[t++] = datas[i++];
        }
    }

    while (i <= Mid) {
        aux_datas[t++] = datas[i++];
    }
    while (j <= R) {
        aux_datas[t++] = datas[j++];
    }

    for (int k = 0; k < t; ++k) {
        datas[L + k] = aux_datas[k];
    }

    return sum;
}

int sumSort(int L, int R)
{
    if (L >= R) {
        return 0;//0表示对于1个元素的不存在翻转数对
    }
    int mid = (L + R) / 2;
    return sumSort(L, mid) + sumSort((mid + 1), R) + merge(L, mid, R);
}

int main(){
    std::scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        std::scanf("%d", &datas[i]);
    }

    int result = sumSort(0, n - 1);

    std::printf("result is %d.\n", result);

    return 0;
}

//---------------------------------------  左神 ------------------------------
package class022;

// 翻转对数量
// 测试链接 : https://leetcode.cn/problems/reverse-pairs/
public class Code02_ReversePairs {

	public static int MAXN = 50001;

	public static int[] help = new int[MAXN];

	public static int reversePairs(int[] arr) {
		return counts(arr, 0, arr.length - 1);
	}

	// 统计l...r范围上，翻转对的数量，同时l...r范围统计完后变有序
	// 时间复杂度O(n * logn)
	public static int counts(int[] arr, int l, int r) {
		if (l == r) {
			return 0;
		}
		int m = (l + r) / 2;
		return counts(arr, l, m) + counts(arr, m + 1, r) + merge(arr, l, m, r);
	}

	public static int merge(int[] arr, int l, int m, int r) {
		// 统计部分
		int ans = 0;
		for (int i = l, j = m + 1; i <= m; i++) {
			while (j <= r && (long) arr[i] > (long) arr[j] * 2) {
				j++;
			}
			ans += j - m - 1;
		}
		// 正常merge
		int i = l;
		int a = l;
		int b = m + 1;
		while (a <= m && b <= r) {
			help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
		}
		while (a <= m) {
			help[i++] = arr[a++];
		}
		while (b <= r) {
			help[i++] = arr[b++];
		}
		for (i = l; i <= r; i++) {
			arr[i] = help[i];
		}
		return ans;
	}

}
