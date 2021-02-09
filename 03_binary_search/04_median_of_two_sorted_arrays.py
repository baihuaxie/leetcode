'''
    problem statement:

    There are two sorted arrays nums1 and nums2 of size m and n respectively.

    Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

    You may assume nums1 and nums2 cannot be both empty.

    didn't solve the problem. below solution is from leetcode forum user MissMary, based on binary search:

    let the two sorted arrays be A[0:m-1] and B[0:n-1]
    assume there is a index pair i, j, they separate the two arrays into left and right parts, such that:
    
    1) len(left_of_A) + len(left_of_B) == len(right_of_A) + len(right_of_B) (m+n is even case; need to +1 if m+n is odd)

    2) max(left_of_A, left_of_B) <= min(right_of_A, right_of_B)
    -> because left_of_A <= right_of_A && left_of_B <= right_of_B by default, this condition is reduced to 
       -> left_of_A <= right_of_B, left_of_B <= right_of_A 

    in such case, we could reliably return the median of the two arrays as follows:

    - if m+n is even, then median = (max(left_of_A, left_of_B) + min(right_of_A, right_of_B)) / 2
    - if m+n is odd, then median = max(left_of_A, left_of_B)

    from condition 1), can deduce a relationship b.t. j and i, so only need to search for i
    - use a binary search to find index i that satisfies condition 2) if j is given by condition 1) => binary search is O(log(n))

    special cases:
    - note that n >= m must hold here, otherwise j could be negative => always search in the shorter array
    - if one array is empty, just return the median of the non-empty array; both can not be empty
    - if i == 0, i == m, j == 0, j == n, then indices may be out of range in condition 2), need to handle them separately
'''


class Solution:

    def findMedianSortedArrays(self, nums1, nums2) -> float:
        A, B, m, n = nums1, nums2, len(nums1), len(nums2)
        # ensures A is always the shorter array & m its length
        if m > n:
            A, B, m, n = B, A, n, m
        # if A is empty, return median value of B directly
        if m == 0:
            return B[n // 2] if n % 2 == 1 else(B[n // 2 - 1] + B[n // 2]) / 2
        # if B is empty, return error because both arrays are empty
        if n == 0:
            raise ValueError
        
        # perform a binary search to find i
        imin, imax = 0, m
        while (imin <= imax):
            # binary search to find i
            i = (imin + imax) // 2
            # from condition 1) for both even and odd cases, can deduce j to take the following form:
            j = (m + n + 1) // 2 - i
            # case 1: if i is too small => increase search region to [i+1, imax]
            if j > 0 and i < m and B[j - 1] > A[i]:
                imin = i + 1
            # case 2: if i is too large => decrease search region to [imin, i-1]
            elif i > 0 and j < n and A[i - 1] > B[j]:
                imax = i - 1
            # case 3: otherwise i is a fit => need to compute the median and return results
            else:

                # find max(left_of_A, left_of_B)
                if i == 0:
                    max_of_left = B[j - 1]
                elif j == 0:
                    max_of_left = A[i - 1]
                else:
                    max_of_left = max(A[i - 1], B[j - 1])
                    
                # find min(right_of_A, right_of_B)
                if j == n:
                    min_of_right = A[i]
                elif i == m:
                    min_of_right = B[j]
                else:
                    min_of_right = min(A[i], B[j])
                    
                # if m+n is even, return average of two middle values; otherwise return the middle value
                if (m + n) % 2 == 1:
                    return max_of_left
                else:
                    return (min_of_right + max_of_left) / 2

                
        
