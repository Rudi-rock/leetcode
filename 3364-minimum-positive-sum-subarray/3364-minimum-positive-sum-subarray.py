class Solution:
    def minimumSumSubarray(self, nums: List[int], l: int, r: int) -> int:
        n = len(nums)
        result = float('inf')
        
        for i in range(n):
            total = 0
            for j in range(i, min(i + r, n)):
                total += nums[j]
                if j - i + 1 >= l and total > 0:
                    result = min(result, total)
        
        return result if result != float('inf') else -1