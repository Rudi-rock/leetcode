class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        int mn = nums[0], mx = nums[0];

        for (int x : nums) {
            mn = min(mn, x);
            mx = max(mx, x);
        }

        unordered_set<int> s(nums.begin(), nums.end());

        for (int i = mn; i <= mx; i++) {
            if (!s.count(i))
                ans.push_back(i);
        }

        return ans;
    }
};