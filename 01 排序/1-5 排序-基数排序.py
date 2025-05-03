## 基数排序(适用于全是整数的情况(负数可平移)；本题是基于计数排序实现的)

import sys

# 输入与初始化
n = int(input())
li = list(map(int, sys.stdin.readline().split()))

# radix_sort函数
def radix_sort(li):
    max_value = max(li)
    exp = 1

    while max_value // exp > 0:
        counting_sort(li, exp)
        exp *= 10
    return

# counting_sort函数(计数排序)
def counting_sort(li, exp):
    li_tem = [0] * n
    counts = [0] * 10

    # 先计数
    for num in li:
        ids = (num // exp) % 10
        counts[ids] += 1

    # 计算前缀和
    for i in range(1, 10):
        counts[i] += counts[i - 1]

    # 逐个移动(要保持稳定性)
    for num in li[::-1]:
        ids = (num // exp) % 10
        counts[ids] -= 1
        li_tem[counts[ids]] = num

    # 转化
    li[:] = li_tem
    return

# 运行输出
radix_sort(li)
print(" ".join(str(x) for x in li))
