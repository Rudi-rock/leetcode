import math
from collections import defaultdict

class Solution:
    def maximumSaleItems(self, items: list[list[int]], budget: int) -> int:
        n = len(items)
        
        factor_count = defaultdict(int)
        for factor, price in items:
            factor_count[factor] += 1
        
        max_factor = n
        multiples_count = [0] * (max_factor + 1)
        for f in range(1, max_factor + 1):
            for mult in range(f, max_factor + 1, f):
                multiples_count[f] += factor_count[mult]
        
        segments = []
        
        for factor, price in items:
            d = multiples_count[factor] - 1
            if d > 0:
                segments.append((2, price, d))
            segments.append((1, price, float('inf')))
        
        segments.sort(key=lambda x: (-x[0] / x[1], -x[0]))
        
        total = 0
        remaining = budget
        
        for val, price, count in segments:
            if remaining <= 0:
                break
            if count == float('inf'):
                copies = remaining // price
                total += copies * val
                remaining -= copies * price
            else:
                copies = min(count, remaining // price)
                total += copies * val
                remaining -= copies * price
        
        return total