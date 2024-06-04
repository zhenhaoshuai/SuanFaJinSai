
/*
这道题和上一道 无重复数值那道题来说 题是一样的，但是 需要我们思考刚刚的逻辑了，
就是 左神那个代码 我们只需要将 i 与 j 相等的时候，这时 我们跳过 这个

*/


void permuteUniqueSolve(vector<int>& source,vector<vector<int>>& result,int dimension)
{
    if (dimension >= source.size()) {
        result.push_back(source);
        return;
    } else {
        std::set<int> setTemp; 
        for (int i = dimension; i < source.size(); ++i) {
            if (0 == setTemp.count(source[i])) //看看这个值是否藏在这个数组中 //来判断这个数是不是来过了
            {
                setTemp.insert(source[i]);//查找这个位置
                std::swap(source[i],source[dimension]);
                permuteUniqueSolve(source, result, dimension + 1);
                std::swap(source[i],source[dimension]); //就是一直在回溯，和移动 不同位置上的值，，，2次交换到回溯时，这个数组中所有的元素都 归位了
            }
        }
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> result;

    std::sort(nums.begin(), nums.end());

    permuteUniqueSolve(nums, result, 0);
    return result;
}

