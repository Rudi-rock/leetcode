class Solution {
    public boolean uniformArray(int[] nums1) {
        boolean hasOdd = false;
        boolean hasEven = false;
        int min = Integer.MAX_VALUE;

        for (int num : nums1) {
            min = Math.min(min, num);

            if (num % 2 == 0) {
                hasEven = true;
            } else {
                hasOdd = true;
            }
        }

        // Already uniform
        if (!hasOdd || !hasEven) {
            return true;
        }

        // Mixed parity: possible only if minimum is odd
        return min % 2 == 1;
    }
}