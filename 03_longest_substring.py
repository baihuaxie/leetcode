'''
    problem statement:

    Given a string, find the length of the longest substring without repeating characters.

    Example 1:

    Input: "abcabcbb"
    Output: 3 
    Explanation: The answer is "abc", with the length of 3. 
'''


'''
    had two submission errors, both related to the handling of boundary cases:

    #1: input '' (empty string), expected output is 0, but output 1
    issue: initialize running_length & maxLength to min of len(s) and 1, instead of just 1

    #2: input 'au' (longest substring = full string), expected output is 2, but output 1
    issue: only has maxLength update syntax in case a), not case b), so cannot handle this situation
    fix:   update maxLength every time the inner while() loop is exited

    learning:
    - always consider boundary cases first; e.g., result = smallest possible value (empty string), or result = largest possible value (full string)
'''

class Solution:

    def lengthOfLongestSubstring(self, s: str) -> int:
        ptr1 = 0
        ptr2 = ptr1 + 1
        running_length = min(1,len(s))
        maxLength = min(1,len(s))
        while ((ptr1 < len(s)) & (ptr2 < len(s))):
            while (ptr1 < ptr2):
                if (s[ptr2] == s[ptr1]):
                    ptr1 += 1
                    ptr2 += 1
                    running_length = ptr2 - ptr1
                    break
                if (ptr1 == ptr2 - 1):
                    ptr1 = ptr1 - running_length + 1
                    running_length += 1
                    ptr2 += 1
                    break
                ptr1 += 1
            maxLength = max(maxLength, running_length)
        return maxLength


if __name__ == "__main__":
    sol = Solution()
    #print(sol.lengthOfLongestSubstring('abcabcbb'))
    #print(sol.lengthOfLongestSubstring('bbbbb'))
    #print(sol.lengthOfLongestSubstring('pwwkew'))
    print(sol.lengthOfLongestSubstring('au'))

