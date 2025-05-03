## 堆排序

import sys

# 输入与初始化
n = int(input())
li = list(map(int, sys.stdin.readline().split()))

# sift函数，在左右子堆都是大根堆的情况下，合并成一个大根堆
def sift(li, root, end):
    i = root
    j = i * 2 + 1
    tem = li[i]
    
    while j <= end:
        if j + 1 <= end and li[j + 1] > li[j]:   # 左右孩子节点取大者
            j += 1
        if li[j] > tem:
            li[i] = li[j]
            i = j
            j = i * 2 + 1
        else:
            break

    li[i] = tem    # 要记得放回来
    return

# heap_sort函数
def heap_sort(li):
    # 形成大根堆
    for i in range((n - 2) // 2, -1, -1):   # 堆的最后一个位置是n-1
        sift(li, i, n - 1)

    # 逐一取出堆顶元素，并重新sift
    for i in range(n - 1):
        li[n - 1 - i], li[0] = li[0], li[n - 1 - i]
        sift(li, 0, n - i - 2)

    return

# 运行输出
heap_sort(li)
print(" ".join(str(x) for x in li))
