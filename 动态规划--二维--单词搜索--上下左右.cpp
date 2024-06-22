/*
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

 

示例 1：


输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true

就是给一个单词组成的网格，问我们能否走出这个 具备这个单词  的网格
*/

//---------- 递归 方式，就是一次递归每次都有4个方向，但是我们暴力递归的话，时间可能不够，所以我们要加上 记忆化搜索


//--- 记忆化搜索


#define UNDEFINESTATE 0
#define NO_ELEMENT 0x0F00 //没有这个元素就 用-1表示
#define UNPASS 0xF000 //解释走这条路不能通过
//因为我们扫描都是从一行进入下一行的，所以进入下一行开始检查上一行时，上一行已经扫描过状态了，就不需要某个方向不同的flag,只要没有这个位置的位标志，这个方向就是不通的

//重要：  其实这种带路径的 递归往往是不需要改成动态规划的，因为动态规划本身就是为了解决重复展开，有大量的缓存命中，发现可以大量的节省展开时间，所以我才有必要改成动态规划
//有反方向关系的 位置关系
#define UP 0x01
#define REVERSE_UP 0x02
#define LEFT 0X04
#define REVERSE_LEFT 0X08
//就是从这个位置到端点的位置 是 ok的flag ,所以来避免重复检查
#define UP_OK 0x10
#define REVERSE_UP_OK 0x20
#define LEFT_OK 0X40
#define REVERSE_LEFT_OK 0X80

bool explore(vector<vector<char>>& board, string& word,vector<vector<unsigned int>>& buffer,int i,int j) {
    if (0x00 != (board[i][j]&(UP|REVERSE_UP))) //证明往上方向是可以的
    {
        if (0x00 != (board[i][j]&UP))
        {
            board[i][j] |= UP_OK;
        }
        if (0x00 != (board[i][j]&REVERSE_UP))
        {
            board[i][j] |= REVERSE_UP_OK;
        }

        explore(board ,word ,buffer ,i-1 ,j);
    }
    

}

/**
 * @brief 
 *  设置一个带路径的递归 --- 左神 还是用了 路径的技巧--使用了递归
 * 
 * 
 * 我的思路还是 使用在第一遍遍历时，就开始判断并标记这个元素是不是这个字符内的，然后添加，如果构成了一个到端的字串就标记为 ‘快完成’ ， 这样来得到答案，我这个是 可以 优化的，但是老师那个也要会
 * 同时我再设置一个 时机，就是当遇到了端点元素之后再开始搜素 被标记为能遍历的 标志
 * 
 * 而左神的是经典代码，直接使用像上次那种 直接递归解决它
 * 
 * 这里我嫌麻烦，就没有给它继续往下写了
 */
 给每个[][] 中都有4个位的关系 
 */
bool exist(vector<vector<char>>& board, string word) {
    vector<vector<unsigned int>> buffer(UNDEFINESTATE);
    // vector<vector<int>> buffer(130, vector<int>(130, -1)); //这里想给这多加一个框来，减少边界的讨论
    int word_pos = 0;//位于当前word的位置
    int wordSize = word.size();
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 1; j < board[i].size(); j++)
        {
            word_pos = str.find(word[board[i][j]]);
            if (i!= 0) //检查 up 方向
            {
                if (word[word_pos-1] == board[i-1][j]) //正序
                {
                    buffer[i][j] |= UP_OK;
                }else if (word[word_pos+1] == board[i-1][j]) //逆序
                {
                    buffer[i][j] |= REVERSE_UP_OK;

                }else{
                    board[i-1][j] = UNPASS; //当 2 头方向都找不到时说明这个 位置是 不再满足我们的搜索的
                }
                if ((word[word_pos-1] == buffer[i][j]) || (word[0] == buffer[i][j]))
                {
                    if (){
                       explore(board ,word ,buffer ,i-1 ,j); //这里发现时机 ，可以触发 区判断这个字符串是否可以，开始搜索
                    }
                    
                    board[i][j] |= UP|REVERSE_UP;
                    bool result 
                }
                

            }else{ //else 用 0 表示，因为这个格子是搜索，过得，当下次我们来找时就不再 过这个格 
                buffer[i][j] = NO_ELEMENT;
            }

            if ((j-1) > 0)
            {
                
            }
            
            
        }
        
    }
    
}

/**
 * @brief 就是使用 把这个点看作是往四周延伸的方向，上面的也可以，但是感觉没有这个优秀 ，这题为什么我想的会那么复杂就是因为没有思考有没有改动态规划的必要
 * 
 * @param board 
 * @param word 
 * @param i 
 * @param j 
 * @param k  word的位置
 * @return true 
 * @return false 
 */
bool existSolve(vector<vector<char>>& board, string& word, int i, int j,int k){
    if (k == word.size()) //因为下面的下面的条件不能进入的话，这个长度的要求也就满足不了
    {
        return true;
    }
    
    if (( i >= board.size()) || ( j >= board[i].size()) || (word[k] != board[i][j]) || ( j < 0) || ( i < 0))
    {
        return false;
    }
    
    char temp = board[i][j];//把走过的点 标记一下，防止重复走过
    board[i][j] = 0;//标记为走过了
    bool ans = existSolve(board,word,i-1,j,k+1)
            || existSolve(board,word,i+1,j,k+1)
            || existSolve(board,word,i,j-1,k+1)
            || existSolve(board,word,i,j+1,k+1);
    board[i][j] = temp;
    return ans;
}

bool exist(vector<vector<char>>& board, string word){
    string wordTemp(word);
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (existSolve(board,wordTemp,i,j,0))
            {
                return true;
            }
        }
    }
    return false;
}

//-----------------------------------------左神

// 单词搜索（无法改成动态规划）
// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word
// 如果 word 存在于网格中，返回 true ；否则，返回 false 。
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成
// 其中"相邻"单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母不允许被重复使用
// 测试链接 : https://leetcode.cn/problems/word-search/
public class Code02_WordSearch {

	public static boolean exist(char[][] board, String word) {
		char[] w = word.toCharArray();
		for (int i = 0; i < board.length; i++) {
			for (int j = 0; j < board[0].length; j++) {
				if (f(board, i, j, w, 0)) {
					return true;
				}
			}
		}
		return false;
	}

	// 因为board会改其中的字符
	// 用来标记哪些字符无法再用
	// 带路径的递归无法改成动态规划或者说没必要
	// 从(i,j)出发，来到w[k]，请问后续能不能把word走出来w[k...]
	public static boolean f(char[][] b, int i, int j, char[] w, int k) {
		if (k == w.length) {
			return true;
		}
		if (i < 0 || i == b.length || j < 0 || j == b[0].length || b[i][j] != w[k]) {
			return false;
		}
		// 不越界，b[i][j] == w[k]
		char tmp = b[i][j];
		b[i][j] = 0;
		boolean ans = f(b, i - 1, j, w, k + 1) 
				|| f(b, i + 1, j, w, k + 1) 
				|| f(b, i, j - 1, w, k + 1)
				|| f(b, i, j + 1, w, k + 1);
		b[i][j] = tmp;
		return ans;
	}

}
