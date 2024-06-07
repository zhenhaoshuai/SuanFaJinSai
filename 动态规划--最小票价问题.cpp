/*
输入：days = [1,4,6,7,8,20] 表示在 这1年 内 第几天有出现安排, costs = [2,7,15] 这里有 3 种方案，A方案：这个票会帮你保管 1天 会花费a元，B方案：保管 7天 花费b元 ,C方案：保管 30 天花费C元
输出：11

题目： 花最少的钱，将这些计划 都安排 下去
*/

#define ARRAY_LEN 100

//-----------------递归做法------最后时间不符合要求-------
//递归做法  把这种方案看作是 一个 多叉树 来处理，每种树都有 多种case
int minCostTicketsSolveBuild(vector<int>& days, vector<int>& costs, vector<int>& dayNums,int pos)
{
    if (pos >= days.size())
    {
        return 0;
    }
    
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < costs.size(); i++){
        int posTemp = pos;
        while ((posTemp < days.size()) && (days[posTemp] < dayNums[i] + days[pos])){ //利用 天数 和 这个票的天数 之间的关系 来得到 下一个的位置
            ++posTemp;
        }
        
        ans = std::min(ans , costs[i] + minCostTicketsSolveBuild(days,costs,dayNums,posTemp));
    }
    return ans;
}

int mincostTickets(vector<int>& days, vector<int>& costs)
{
    std::vector<int> buffer(ARRAY_LEN, -1);  // 这个用来存这个2天的
    std::vector<int> dayNums{1,7,30}; //天数

    return minCostTicketsSolveBuild(days ,costs ,dayNums,0);
}


