//1659. 最大化网格幸福感 显示英文描述
//给你四个整数 m、n、introvertsCount 和 extrovertsCount 。有一个 m x n 网格，和两种类型的人：内向的人和外向的人。总共有 introvertsCount 个内向的人和 extrovertsCount 个外向的人。
//
//请你决定网格中应当居住多少人，并为每个人分配一个网格单元。 注意，不必 让所有人都生活在网格中。
//
//每个人的 幸福感 计算如下：
//
//内向的人 开始 时有 120 个幸福感，但每存在一个邻居（内向的或外向的）他都会 失去  30 个幸福感。
//外向的人 开始 时有 40 个幸福感，每存在一个邻居（内向的或外向的）他都会 得到  20 个幸福感。
//邻居是指居住在一个人所在单元的上、下、左、右四个直接相邻的单元中的其他人。
//
//网格幸福感 是每个人幸福感的 总和 。 返回 最大可能的网格幸福感 。
//
//输入：m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
//输出：240
//解释：假设网格坐标 (row, column) 从 1 开始编号。
//将内向的人放置在单元 (1,1) ，将外向的人放置在单元 (1,3) 和 (2,3) 。
//- 位于 (1,1) 的内向的人的幸福感：120（初始幸福感）- (0 * 30)（0 位邻居）= 120
//- 位于 (1,3) 的外向的人的幸福感：40（初始幸福感）+ (1 * 20)（1 位邻居）= 60
//- 位于 (2,3) 的外向的人的幸福感：40（初始幸福感）+ (1 * 20)（1 位邻居）= 60
//网格幸福感为：120 + 60 + 60 = 240

#include <bits/stdc++.h>


using namespace std;

class Solution {
public:
    int getMaxGridHappiness(int m, int n, int intC, int extC) {
        memset(dp,-1,sizeof dp);
        return dfs(m,n,0,0,0,intC,extC);
    }
    int dp[6][6][729][7][7];
    int H[3][3]={0,0,0,0,-60,-10,0,-10,40};
    int dfs(int m, int n, int r,int c,int st,int intC, int extC){
        if(r==m)return 0;
        if(dp[r][c][st][intC][extC]!=-1)return dp[r][c][st][intC][extC];
        int nr=(c==n-1)?r+1:r;
        int nc=(c==n-1)?0:c+1;
        int head=st/static_cast<int>(pow(3,n-1)),pre=st%static_cast<int>(pow(3,n-1)),tail=st%3;
        dp[r][c][st][intC][extC]=dfs(m,n,nr,nc,pre*3,intC,extC);
        if(intC>0){
            dp[r][c][st][intC][extC]=max(dp[r][c][st][intC][extC],H[head][1]+120+dfs(m,n,nr,nc,pre*3+1,intC-1,extC)+(c>0?H[tail][1]:0));
        }
        if(extC>0){
            dp[r][c][st][intC][extC]=max(dp[r][c][st][intC][extC],H[head][2]+40+dfs(m,n,nr,nc,pre*3+2,intC,extC-1)+(c!=0?H[tail][2]:0));
        }
        return dp[r][c][st][intC][extC];
    }
};

int main(int argc, const char * argv[]) {
    Solution s;
    cout<<s.getMaxGridHappiness(2, 3, 1, 2)<<endl;
    return 0;
}
