最大化一个序列的子序列的最小值


#include <iostream>
#include "vector"
#include <numeric>

using namespace std;

vector<int> x;
int n;//sequence
int c;//bull nums

int ans = 0;
int shift_Flg = 0;


bool canSplit(std::vector<int> &nums, int max)
{
    int count = 0;
    int countSum = 0;

    for (int num: nums) {
        if (countSum + num > max) {
            count++;
            countSum = num;
            if (count > c) {
                return false;
            }
        } else {
            countSum += num;
        }
    }

    return true;
}


int main() {
    using namespace std;
    std::scanf("%d %d", &n, &c);
    int temp = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        x.push_back(temp);
    }

    sort(x.begin(), x.end());

    int low = *std::max_element(x.begin(), x.end());
    int max = std::accumulate(x.begin(),x.end(),0);

    while (low < max)
    {
        int mid = (low + max) >> 1;

        if (canSplit(x,mid)) {
            max = mid; //这里是关键，因为你CanSplit返回可以继续分割是因为，我们每次都是从头走到尾，但是我们此题是求 最大的最小值，所以还要继续分割
        } else {
            low = mid +1;
        }
    }


    cout << "最小值最大化 值 = " << low << endl;
    return 0;
}


//-------------------------一下是资料

#include <iostream>
#include <vector>
#include <numeric>

// 检查是否可以将数组 nums 分割成 N 个子序列，使得每个子序列的和都不大于 maxSum
bool canSplit(const std::vector<int>& nums, int N, int maxSum) {
    int count = 1;
    int currentSum = 0;

    for (int num : nums) {
        if (currentSum + num > maxSum) {
            count++;
            currentSum = num;
            if (count > N) return false;
        } else {
            currentSum += num;
        }
    }

    return true;
}

int splitArray(std::vector<int>& nums, int N) {
    // 使用二分查找确定可能的最大最小值范围
    int low = *std::max_element(nums.begin(), nums.end());
    int high = std::accumulate(nums.begin(), nums.end(), 0);

    while (low < high) {
        int mid = low + (high - low) / 2;
        
        if (canSplit(nums, N, mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return low;
}

int main() {
    std::vector<int> nums = {7, 2, 5, 10, 8};
    int N = 2;

    int maxMinValue = splitArray(nums, N);

    std::cout << "The maximum minimum value of " << N << " subarrays is: " << maxMinValue << std::endl;

    return 0;
}


当然可以，这道题的核心是在给定的数组中，找到一个最大的最小值，这样可以将数组分割成 N 个子序列，使得每个子序列的和都不超过这个最大的最小值。

算法解析：
步骤 1：确定最小值的范围
下界： 最小的可能的最小值是数组中的最大元素。因为每个子序列的和至少要大于或等于数组中的最大元素。
上界： 最大的可能的最小值是整个数组的和。因为如果每个子序列的和等于整个数组的和，那么数组就不需要被分割。
在代码中，我们使用 std::max_element 来找到数组中的最大元素，并使用 std::accumulate 来计算数组的总和。

步骤 2：使用二分查找确定可能的最大最小值
我们使用二分查找在上述确定的范围内搜索可能的最大最小值。

步骤 3：使用贪心算法尝试分割数组
对于每一个可能的最大最小值，我们使用贪心算法来尝试分割数组。

贪心策略： 尽可能地将当前元素添加到当前子序列中，直到当前子序列的和超过最大最小值。
如果超过了最大最小值，我们就开始一个新的子序列。
步骤 4：根据贪心算法的结果调整二分查找的范围
如果数组可以被分割成 N 个子序列，那么我们尝试寻找一个更大的最大最小值，即减小上界。
如果数组不能被分割成 N 个子序列，那么我们尝试寻找一个更小的最大最小值，即增加下界。
