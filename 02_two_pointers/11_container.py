"""
    Problem:

    Given an array of n non-negative integers, [a1,a2,...,an], find the maximum value of the following expression:

    (j-i)*min(a[i],a[j]), where i and j are indices

    (figuritively, this is the 'container' which can hold maximum volume of water)

"""


class Solution:
    def maxArea_n2(self, height) -> int:
        """
        Solution:

        do a naive O(n^2) iteration

        - this solution works but takes too long for OJ to accept!
        - need to find an O(n) solution
        """

        maxArea = 0

        for i in range(0, len(height)-1):
            for j in range(i+1, len(height)):
                area = (j - i) * min(height[i], height[j])
                if area > maxArea:
                    maxArea = area

        return maxArea


    def maxArea(self, height) -> int:
        """
        Solution:

        O(n) solution by iterating index i from head and index j from tail simultaneously
        - in any iteration, only need to move the index which had smaller height
        - keep a booking on maximum area
        """

        maxArea = 0
        i = 0
        j = len(height)-1
        
        while(i != j):
            if height[i] <= height[j]:
                minHeight = height[i]
                i += 1
            else:
                minHeight = height[j]
                j -= 1
            area = (j - i + 1) * minHeight
            if area > maxArea:
                maxArea = area

        return maxArea
