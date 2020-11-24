""" test leetcode-11 container with most water solution """

import pytest
Solution = __import__('07_11_container').Solution

@pytest.mark.parametrize("s,res", [([1, 8, 6, 2, 5, 4, 8, 3, 7], 49),
([0, 0], 0), ([0, 1], 0)])
def test_container_n2(s, res):
    """ test calculated results """
    sol = Solution()
    assert sol.maxArea_n2(s) == res, "- matching error"


@pytest.mark.parametrize("s,res", [([1, 8, 6, 2, 5, 4, 8, 3, 7], 49),
                                   ([0, 0], 0), ([0, 1], 0)])
def test_container(s, res):
    """ test calculated results """
    sol = Solution()
    assert sol.maxArea(s) == res, "- matching error"
