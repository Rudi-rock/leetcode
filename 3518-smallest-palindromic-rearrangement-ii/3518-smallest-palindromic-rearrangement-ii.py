from collections import Counter
from math import comb

class Solution:
    def smallestPalindrome(self, s, k):
        LIMIT = 10**6

        cnt = Counter(s)

        half = [0] * 26
        mid = ""

        for c in sorted(cnt):
            if cnt[c] % 2:
                mid = c
            half[ord(c) - ord("a")] = cnt[c] // 2

        def ways(freq):
            total = sum(freq)
            ans = 1
            rem = total
            for x in freq:
                if x:
                    ans *= comb(rem, x)
                    if ans > LIMIT:
                        return LIMIT + 1
                    rem -= x
            return ans

        if ways(half) < k:
            return ""

        left = []

        while sum(half):
            for i in range(26):
                if half[i] == 0:
                    continue

                half[i] -= 1
                w = ways(half)

                if w >= k:
                    left.append(chr(i + ord("a")))
                    break
                else:
                    k -= w
                    half[i] += 1

        left = "".join(left)
        return left + mid + left[::-1]