class Solution {
  public int maxPalindromes(String s, int k) {
    final int n = s.length();
    // dp[i] := the maximum number of substrings in the first i chars of s
    int[] dp = new int[n + 1];

    for (int i = k; i <= n; ++i) {
      dp[i] = dp[i - 1];
      // Consider palindrome with length k.
      if (isPalindrome(s, i - k, i - 1))
        dp[i] = Math.max(dp[i], 1 + dp[i - k]);
      // Consider palindrome with length k + 1.
      if (isPalindrome(s, i - k - 1, i - 1))
        dp[i] = Math.max(dp[i], 1 + dp[i - k - 1]);
    }

    return dp[n];
  }

  private boolean isPalindrome(String s, int l, int r) {
    if (l < 0)
      return false;
    while (l < r)
      if (s.charAt(l++) != s.charAt(r--))
        return false;
    return true;
  }
}