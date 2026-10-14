class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        // Check if it's possible
        if (sum > 9 * num || (sum == 0 && num > 1)) {
            return "";
        }
        
        // Special case: sum = 0 with num = 1
        if (sum == 0) {
            return "0";
        }
        
        // Greedy construction: fill from left to right with largest possible digits
        string result(num, '0');
        int remaining_sum = sum;
        
        for (int i = 0; i < num; i++) {
            // Maximum digit we can place at position i
            int digit = min(9, remaining_sum);
            result[i] = '0' + digit;
            remaining_sum -= digit;
        }
        
        // If we couldn't distribute all of sum, it's impossible
        if (remaining_sum > 0) {
            return "";
        }
        
        return result;
    }
};