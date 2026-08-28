class Solution {

    public String lexPalindromicPermutation(String s, String target) {
        int n = s.length();
        int[] freq = new int[26];

        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        int oddCount = 0;
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            if ((freq[i] & 1) == 1) {
                oddCount++;
                middle = (char) ('a' + i);
            }
        }

        // More than one odd frequency means palindrome is impossible
        if (oddCount > 1) {
            return "";
        }

        int halfLen = n / 2;

        int[] base = new int[26];
        for (int i = 0; i < 26; i++) {
            base[i] = freq[i] / 2;
        }

        String prefix = target.substring(0, halfLen);

        // Try using target's first half exactly
        int[] count = base.clone();
        boolean possible = true;

        for (char c : prefix.toCharArray()) {
            int idx = c - 'a';

            if (count[idx] == 0) {
                possible = false;
                break;
            }

            count[idx]--;
        }

        if (possible) {
            String candidate = buildPalindrome(prefix, middle, oddCount);

            if (candidate.compareTo(target) > 0) {
                return candidate;
            }
        }

        // Find smallest valid first half strictly greater than prefix
        for (int pivot = halfLen - 1; pivot >= 0; pivot--) {

            count = base.clone();
            boolean valid = true;

            // Keep everything before pivot equal
            for (int i = 0; i < pivot; i++) {
                int idx = prefix.charAt(i) - 'a';

                if (count[idx] == 0) {
                    valid = false;
                    break;
                }

                count[idx]--;
            }

            if (!valid) {
                continue;
            }

            // Find smallest character greater than prefix[pivot]
            int current = prefix.charAt(pivot) - 'a';
            int chosen = -1;

            for (int c = current + 1; c < 26; c++) {
                if (count[c] > 0) {
                    chosen = c;
                    break;
                }
            }

            if (chosen == -1) {
                continue;
            }

            StringBuilder half = new StringBuilder();

            // Same prefix before pivot
            half.append(prefix, 0, pivot);

            // Larger character at pivot
            half.append((char) ('a' + chosen));
            count[chosen]--;

            // Smallest possible remaining suffix
            for (int c = 0; c < 26; c++) {
                while (count[c] > 0) {
                    half.append((char) ('a' + c));
                    count[c]--;
                }
            }

            return buildPalindrome(half.toString(), middle, oddCount);
        }

        return "";
    }

    private String buildPalindrome(String half, char middle, int oddCount) {
        StringBuilder result = new StringBuilder(half);

        if (oddCount == 1) {
            result.append(middle);
        }

        result.append(new StringBuilder(half).reverse());

        return result.toString();
    }
}