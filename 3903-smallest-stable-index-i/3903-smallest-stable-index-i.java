class Solution {
    public int firstStableIndex(int[] nums, int k) {
        int n = nums.length;

        for (int i = 0; i < n; i++) {
            int prefixMax = Integer.MIN_VALUE;
            int suffixMin = Integer.MAX_VALUE;

            for (int j = 0; j <= i; j++) {
                prefixMax = Math.max(prefixMax, nums[j]);
            }

            for (int j = i; j < n; j++) {
                suffixMin = Math.min(suffixMin, nums[j]);
            }

            if ((long) prefixMax - suffixMin <= k) {
                return i;
            }
        }

        return -1;
    }
}