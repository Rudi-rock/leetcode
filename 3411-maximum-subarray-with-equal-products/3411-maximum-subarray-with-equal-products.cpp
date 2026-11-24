class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int best = 1;
        
        for (int i = 0; i < n; i++) {
            long long prod = 1, g = nums[i], l = nums[i];
            for (int j = i; j < n; j++) {
                g = __gcd(g, (long long)nums[j]);
                l = l / __gcd(l, (long long)nums[j]) * nums[j];
                // cap prod to avoid overflow
                if (prod <= 1e15)
                    prod *= nums[j];
                else
                    prod = l * g + 1; // force inequality
                if (prod == l * g)
                    best = max(best, j - i + 1);
            }
        }
        
        return best;
    }
};