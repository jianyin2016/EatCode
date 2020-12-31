#include <bits/stdc++.h>
using namespace std;

// ST(sparse table) algorithms
const int MAXN = 1010;
int dp[MAXN][10];
int mm[MAXN];
void initRMQ(vector<int>& arr)
{
	int n = arr.size();
	mm[0] = -1;
	for (int i = 1; i <= n; i++)
	{
		mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
		dp[i][0] = i - 1;
	}
	for (int j = 1; j <= mm[n]; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			dp[i][j] = arr[dp[i][j - 1]] > arr[dp[i + (1 << (j - 1))][j - 1]] ? dp[i][j - 1] : dp[i + (1 << (j - 1))][j - 1];
}

//index of maximum
int RMQ(vector<int>& arr, int L, int R) {
	int k = mm[R - L + 1];
	return arr[dp[L][k]] >= arr[dp[R - (1 << k) + 1][k]] ? dp[L][k] : dp[R - (1 << k) + 1][k];
}
int main()
{
	vector<int>arr = { 3,1,5,6,7,2,5,2,3,10,99 };
	initRMQ(arr);
	std::cout << arr[RMQ(arr, 0, 5)] << endl;
}


