
//先序 序列化
std::string  serilize(TreeNode* root)
{
   std::string ans("");
   if(root == nullptr){
      return  "#";
   }
   ans = to_string(root->val) + "，" + serilize(root->Left) + "," + anserilize(root->Right);
   return ans;
}


