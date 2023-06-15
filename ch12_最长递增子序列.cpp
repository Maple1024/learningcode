//300. 最长递增子序列
//给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
//子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
//例如，[3, 6, 2, 7] 是数组[0, 3, 1, 6, 2, 2, 7] 的子序列。
/*
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。

输入：nums = [0,1,0,3,2,3]
输出：4

*/
#include <iostream>
#include <vector>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
	int ans = 0;
	int n = nums.size();
	vector<int> dp(n,1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (nums[i] > nums[j]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
	return dp[n - 1];
}

int lengthOfLIS2(vector<int>& nums) {
	vector<int>tmp;
	int ans = 1,n=nums.size();
	tmp.push_back(nums[0]);
	for(int i = 1; i < n; i++) {
		if (nums[i] > tmp.back()) {
			tmp.push_back(nums[i]);
			ans++;
		}
		else {
			int left = 0, right = tmp.size() - 1;
			while (left < right) {
				int mid = (left + right) >> 1;
				if (nums[i] > tmp[mid]) {
					left = mid + 1;
				}
				else {
					right = mid;
				}
			}
			tmp[right] = nums[i];
		}
	}
	for (auto& k : tmp) {
		cout << k << " ";
	}
	cout << endl;
	return ans ;
}
int main() {
	vector<int>tmp = { 0,1,0,3,2,3 };
	int ans = lengthOfLIS2(tmp);
	cout << "ans= " <<ans<< endl;
}



