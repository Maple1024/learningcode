/*
��ָ Offer II 008. �ʹ��ڵ��� target �����������
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
            //�ӵ�0��Ŀ�꿪ʼ��
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