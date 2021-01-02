//1632. 矩阵转换后的秩
//给你一个 m x n 的矩阵 matrix ，请你返回一个新的矩阵 answer ，其中 answer[row][col] 是 matrix[row][col] 的秩。
//
//每个元素的 秩 是一个整数，表示这个元素相对于其他元素的大小关系，它按照如下规则计算：
//
//秩是从 1 开始的一个整数。
//如果两个元素 p 和 q 在 同一行 或者 同一列 ，那么：
//如果 p < q ，那么 rank(p) < rank(q)
//如果 p == q ，那么 rank(p) == rank(q)
//如果 p > q ，那么 rank(p) > rank(q)
//秩 需要越 小 越好。
//题目保证按照上面规则 answer 数组是唯一的。
//
//
//
//示例 1：
//
//
//输入：matrix = [[1,2],[3,4]]
//输出：[[1,2],[2,3]]
//解释：
//matrix[0][0] 的秩为 1 ，因为它是所在行和列的最小整数。
//matrix[0][1] 的秩为 2 ，因为 matrix[0][1] > matrix[0][0] 且 matrix[0][0] 的秩为 1 。
//matrix[1][0] 的秩为 2 ，因为 matrix[1][0] > matrix[0][0] 且 matrix[0][0] 的秩为 1 。
//matrix[1][1] 的秩为 3 ，因为 matrix[1][1] > matrix[0][1]， matrix[1][1] > matrix[1][0] 且 matrix[0][1] 和matrix[1][0] 的秩都为 2 。
#include <bits/stdc++.h>

using  namespace std;

class Solution {
public:
    const static int M=512;
    int p[M*2];
    void init(){
        for(int i=0;i<M*2;++i)p[i]=i;
    }
    int find(int x){
        if(x==p[x])return x;
        return p[x]=find(p[x]);
    }
    void unite(int x,int y){
        x=find(x),y=find(y);
        p[y]=x;
    }
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
//      step1，由小到大计算rank，先按大小分组，若相等且位于同一行或同一列则受rank相同制约
//      step2，用并查集维护行列关系，做r->r，c->c+M的变换可以用一个并查集维护
//      step3，每一个独立组的rank取本组元素坐在行列中rank最大值+1，等值的元素可能构成多个独立组。
        int n=matrix.size(),m=matrix[0].size();
        vector<int>maxR(n),maxC(m);
        vector<vector<int>>ans(n,vector<int>(m));
        unordered_map<int,vector<int>>mp,g;
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                mp[matrix[i][j]].push_back(i*M+j);
            }
        }
        vector<int>values(mp.size());
        int t=0;
        for(auto&[v,_]:mp)values[t++]=v;
        sort(values.begin(),values.end());
        init();
        for(int v:values){
            g.clear();
            for(int pos:mp[v])unite(pos/M,pos%M+M);
            for(int pos:mp[v])g[find(pos/M)].push_back(pos);
            for(auto&[_,group]:g){
                int rank=0;
                //rank取等rank制约的元素中最大rank+1
                for(int pos:group)
                    rank=max({rank,maxR[pos/M],maxC[pos%M]});
                rank+=1;
                for(int pos:group){
                    maxR[pos/M]=maxC[pos%M]=ans[pos/M][pos%M]=rank;
                    p[pos/M]=pos/M,p[pos%M+M]=pos%M+M;
                }
            }
        }
        return ans;
    }
};

int main(int argc, const char * argv[]) {
    vector<vector<int>>matrix={{1,2},{3,4}};
    Solution s;
    auto ans=s.matrixRankTransform(matrix);
    for(int i=0;i<matrix.size();++i){
        for(int j=0;j<matrix[0].size();++j){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
