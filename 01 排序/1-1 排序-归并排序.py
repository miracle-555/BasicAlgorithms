## 归并排序(分治+递归)

import sys

# 输入与初始化
n = int(input())
li = list(map(int, sys.stdin.readline().split()))

# merge函数，把已经排好的两个数组归并成一个
def merge(li, start, mid, end):
    li_tem = [0] * (end - start + 1)
    i = start
    j = mid + 1
    k = 0
    
    while i <= mid and j <= end:
        if li[i] <= li[j]:
            li_tem[k] = li[i]
            i += 1
        else:
            li_tem[k] = li[j]
            j += 1
        k += 1
        
    while i <= mid:
        li_tem[k] = li[i]
        i += 1
        k += 1

    while j <= end:
        li_tem[k] = li[j]
        j += 1
        k += 1

    li[start:end + 1] = li_tem
    return

# merge_sort函数，排好任一数组
def merge_sort(li, start, end):
    if start < end:
        mid = (start + end) // 2
        merge_sort(li, start, mid)
        merge_sort(li, mid + 1, end)
        merge(li, start, mid, end)
    return 

# 运行输出
merge_sort(li, 0, n - 1)
print(" ".join(str(x) for x in li))
