## 快速排序(分治+递归)

import sys

# 输入与初始化
n = int(input())
li = list(map(int, sys.stdin.readline().split()))

# partition函数，以一个数为基准，小往左丢，大往右丢
def partition(li, i, j):
    tem = li[j]
    
    while i < j:
        while i < j and li[i] <= tem:   # 先从另一边开始
            i += 1
        else:
            li[j] = li[i]
            
        while i < j and li[j] >= tem:
            j -= 1
        else:
            li[i] = li[j]

    li[i] = tem
    return i

# quick_sort函数，直接排序
def quick_sort(li, i, j):
    if i < j:
        mid = partition(li, i, j)
        quick_sort(li, i, mid - 1)
        quick_sort(li, mid + 1, j)
        
    return

# 运行输出
quick_sort(li, 0, n - 1)
print(" ".join(str(x) for x in li))
