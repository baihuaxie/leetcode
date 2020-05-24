class Solution:
    """ solution to two sums problem """
    def __init__(self):
        """ empty constructor """
        pass

    def twoSum(self, nums, target) :
        arr_res = []
        for i in range(0,len(nums)):
            if not arr_res:
                arr_res.append(target - nums[i])
            else:
                try:
                    z = arr_res.index(nums[i])
                except ValueError:
                    arr_res.append(target - nums[i])
                    continue
                return [z, i]
        return "no match!"


"""    
    submit #1: error

    in the following code, the issue was that if the test case contain identical elements, then nums.index(x) always return the first element index
    e.g., nums=[3,3], target=6; should return [0,1], but the code will return [0,0]
    solution => change to use "for i ..." structure

    def twoSum(self, nums, target) :
        arr_res = []
        for x in nums:
            if not arr_res:
                arr_res.append(target - x)
            else:
                try:
                    z = arr_res.index(x)
                except ValueError:
                    arr_res.append(target - x)
                    continue
                return [z, nums.index(x)]
        return "no match!"
"""




if __name__ == "__main__":
    nums = [3,3]
    target = 6
    sol = Solution()
    print(sol.twoSum(nums,target))
