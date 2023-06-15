/*
剑指 Offer II 008. 和大于等于 target 的最短子数组
*/
#include <vector>
#include <limits>
using namespace std;
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        vector<int>dp(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1] + nums[i - 1];
        }

        int ans = INT_MAX;
        for (int i = 1; i <= n; i++) {
            //从第0个目标开始找
            int s = target + dp[i - 1];
            int position = find(s, dp);
            if (position <= n) {
                ans = min(ans, position - i + 1);
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
    int find(int s, vector<int>& dp) {
        int left = 1, right = dp.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (s > dp[mid]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;

    }
};