
/*
一个正整数如果能被 a 或 b 整除，那么它是神奇的。

给定三个整数 n , a , b ，返回第 n 个神奇的数字。因为答案可能很大，所以返回答案 对 109 + 7 取模 后的值。

 

示例 1：

输入：n = 1, a = 2, b = 3
输出：2
示例 2：

输入：n = 4, a = 2, b = 3
输出：6
 

提示：

1 <= n <= 109
2 <= a, b <= 4 * 104
*/

//-------------------------递归写法
const long long MI = 1e9+7;

long long nthMagicalNumberSolve(int n, int a, int b, long long l, long long r){ // 这里把int 变为 long long 就是因为使用过程中发现长度不够
    // int x = n * min(a,b);
    
    if (l == r) //因为最后的时候由上一个递归给的值就是l = r 了
    {
        return r%MI;
    }
    long long mid = (r+l)/2;
    long long min_lcm = std::lcm(a,b);//得到a 和 b之间的最小公倍数
    long long mid_ans = (mid/a) + (mid/b) - (mid/min_lcm); //利用容斥原理得结果
    
    if (mid_ans >= n)
    {
        return nthMagicalNumberSolve(n,a,b,l,mid);
    }else{
        return nthMagicalNumberSolve(n,a,b,mid+1,r);
    }
}

int nthMagicalNumber(int n, int a, int b) {
    return (n==0)? 0 : nthMagicalNumberSolve(n,a,b,1,1LL * n * min(a,b));
} 

//--------------------- 使用在一个 for 循环内完成 ，避免了 递归的多余内存的使用
const long long MI = 1e9 + 7;
int nthMagicalNumber(int n, int a, int b) {
    
    long long mid = 0;
    long long min_lcm = std::lcm(a,b);
    long long mid_ans = 0;
    long long  answer = 0;
    //同理还是利用 这个结果一定存在 ，所以肯定有 l = r
    for (long long l = 1,r = 1LL * n * min(a,b); l <= r;)
    {
        mid = (r+l)/2;
        mid_ans = (mid/a) + (mid/b) - (mid/min_lcm); 

        if (mid_ans >= n)
        {
            answer = mid;
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return answer % MI;
}

//-----------------------------       左神
// 给定三个整数 n , a , b ，返回第 n 个神奇的数字。
// 因为答案可能很大，所以返回答案 对 10^9 + 7 取模 后的值。
// 测试链接 : https://leetcode.cn/problems/nth-magical-number/
public class Code02_NthMagicalNumber {

	public static int nthMagicalNumber(int n, int a, int b) {
		long lcm = lcm(a, b);
		long ans = 0;
		// l = 0
		// r = (long) n * Math.min(a, b)
		// l......r
		for (long l = 0, r = (long) n * Math.min(a, b), m = 0; l <= r;) {
			m = (l + r) / 2;
			// 1....m
			if (m / a + m / b - m / lcm >= n) {
				ans = m;
				r = m - 1;
			} else {
				l = m + 1;
			}
		}
		return (int) (ans % 1000000007);
	}

	public static long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	public static long lcm(long a, long b) {
		return (long) a / gcd(a, b) * b;
	}

}



