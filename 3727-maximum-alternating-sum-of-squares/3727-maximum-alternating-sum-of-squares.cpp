class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return abs(a) < abs(b);
        });
        
        long long score = 0;
        int left = 0, right = nums.size() - 1;
        bool isPositive = true;
        
        while (left <= right) {
            long long val;
            if (isPositive) {
                val = (long long)nums[right] * nums[right];
                right--;
                score += val;
            } else {
                val = (long long)nums[left] * nums[left];
                left++;
                score -= val;
            }
            isPositive = !isPositive;
        }
        
        return score;
    }
};