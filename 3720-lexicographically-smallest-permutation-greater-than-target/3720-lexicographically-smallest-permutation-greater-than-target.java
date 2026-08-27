class Solution {
    public String lexGreaterPermutation(String s, String target) {
        int n = s.length();
        int[] freq = new int[26];

        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        StringBuilder prefix = new StringBuilder();

        // First, match target as far as possible
        for (int i = 0; i < n; i++) {
            int cur = target.charAt(i) - 'a';

            if (freq[cur] > 0) {
                prefix.append(target.charAt(i));
                freq[cur]--;
            } else {
                break;
            }
        }

        // Backtrack from right to left.
        // Find the rightmost position where we can use
        // a character greater than target[i].
        for (int i = prefix.length(); i >= 0; i--) {

            if (i < prefix.length()) {
                char removed = prefix.charAt(prefix.length() - 1);
                prefix.deleteCharAt(prefix.length() - 1);
                freq[removed - 'a']++;
            }

            if (i == n) continue;

            int cur = target.charAt(i) - 'a';

            // Find smallest available character > target[i]
            for (int c = cur + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    StringBuilder ans = new StringBuilder(prefix);
                    ans.append((char) ('a' + c));
                    freq[c]--;

                    // Append remaining characters in sorted order
                    for (int j = 0; j < 26; j++) {
                        while (freq[j] > 0) {
                            ans.append((char) ('a' + j));
                            freq[j]--;
                        }
                    }

                    return ans.toString();
                }
            }
        }

        return "";
    }
}