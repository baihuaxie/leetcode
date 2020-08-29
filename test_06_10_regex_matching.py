""" test leetcode-10 regex matching solution """

import pytest
Solution = __import__('06_10_regex_matching').Solution


@pytest.mark.parametrize("s,p,res", [('ab', '.*', True),
('aab', 'c*a*b', True), ('mississippi', 'mis*is*p*.', False), ('aa', 'a', False),
('aa', 'a*', True), ('mississippi', '.*mis.*sip.*i', True), ('', 'a.*', False), ('abcd', '', False), ('', '.', False), ('', '.*', True), ('', '...*.*.*', False), ('', 'a*b*c*', True),
    ('', 'a*bb*c*', False), ('abcd', '.*', True), ('mississippi', 'mis*is*ip*.', True), ('aaa', 'aa', False), ('a', 'ab*', True)])
def test_regex_matching(s, p, res):
    """ test matching results """
    sol = Solution()
    assert sol.isMatch(s, p) == res, "- matching error"
