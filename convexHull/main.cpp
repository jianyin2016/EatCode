#include<bits/stdc++.h>
using namespace std;

//Determine Convex Hull for Planar Scattered Point Set
vector<vector<int>> andrew(vector<vector<int>>& points) {
	int n = points.size(), t = 0;
	auto ans = vector<vector<int>>(2 * n);
	sort(points.begin(), points.end(), [](const vector<int>& l, const vector<int>& r) {return l[0] < r[0] || (l[0] == r[0] && l[1] < r[1]); });
	auto outerProd = [](const vector<int>& p0, const vector<int>& p1, const vector<int>& p2) {
		return (p1[0] - p0[0]) * (p2[1] - p0[1]) - (p1[1] - p0[1]) * (p2[0] - p0[0]);
	};
	for (int i = 0; i < n; ++i) {
		while (t > 1 && outerProd(ans[t - 2], ans[t - 1], points[i]) < 0) {
			--t;
		}
		ans[t++] = points[i];
	}
	int k = t;
	for (int i = n - 2; i >= 0; --i) {
		while (t > k && outerProd(ans[t - 2], ans[t - 1], points[i]) < 0) {
			--t;
		}
		ans[t++] = points[i];
	}
	if (n > 1)t--;
	ans.resize(t);
	return ans;
}

int main(){
	return -1;
}