def removeElement(nums, val):
    """
    :type nums: List[int]
    :type val: int
    :rtype: int
    """
    i = 0

    while i < len(nums):
        if nums[i] == val:
            nums.remove(nums[i])
            i -= 1
        else:
            i += 1

def removeDuplicates(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    i = 1
    prevval = nums[0]
    count = 1

    while i < len(nums):
        if nums[i] == prevval:
            count += 1
            prevval = nums[i]
                
            if count >= 3:
                nums.remove(nums[i])
                i -= 1
            else:
                i += 1

        else:
            i += 1
            count = 1
        
			

if __name__ == '__main__':

    nums = [0,1,1,1,2,2,3,0,4,2]
    val = 2
    removeElement(nums, val)
    print(nums)