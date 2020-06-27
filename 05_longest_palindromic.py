"""
    Longest palindromic substring

    Given a string s, return the longest palindromic substring

"""


class Solution:

    def longestPalindrome(self, s: str) -> str:
        """
        Solution to longest palindromic substring:

        let s be a string of length m

        reverse s in order:
        s_bar = reverse(s) 

        let the longest palindromic substring has length k
        - in original string s => s[i, i+k-1]
        - in reversed string s_bar => s_bar[j, l]
        
        we have the following relationship:
        - s[i, i+k-1] == s_bar[j, l]
        - 0<=i<=m-1, 1<=k<=m-i
        - m-1-l+1 = i+1 => l = m-i-1
        - l-j+1 = k => j = m-i-k

        thus we could find the substring by:

        s_bar = reverse(s)
        res = s[0]

        for i in range(0, m):
            for k in range(len(res), m-i+1):
                j = m-i-k
                l = m-i-1
                if s[i,i+k-1] == s_bar[j,l]:
                    res = s[i, i+k-1]
        return res

        """

        if len(s) == 0:
            return ''

        s_bar = s[::-1]
        res = s[0]
        m =len(s)
        for i in range(0, m):
            if len(res) <= m - i - 1:
                for k in range(len(res)+1, m-i+1):
                    j = m - i - k
                    l = m - i
                    if s[i:i+k] == s_bar[j:l]:
                        res = s[i:i+k]

        return res


if __name__ == '__main__':
    sol = Solution()
    sol.longestPalindrome('aaaa')