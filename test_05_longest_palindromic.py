"""
    Tests for leetcode-05 longest palindromic substring
"""

import pytest
Solution = __import__('05_longest_palindromic').Solution

@pytest.mark.skip
@pytest.mark.parametrize("s, s_bar", [('abcd','dcba'),('aabcdcbf','fbcdcbaa')])
def test_reverse_str(s, s_bar):
    """ test reversing string s """
    sol = Solution()
    assert sol.longestPalindrome(s) == s_bar, "- string reversing error"


@pytest.mark.parametrize("s,res",[('aaaa','aaaa'),('abcde','a'),('babad','bab'), ('cbabc','cbabc'), ('aabcdcbf','bcdcb')])
def test_result(s, res):
    """ test finding longest palindrome """
    sol = Solution()
    assert sol.longestPalindrome(s) == res