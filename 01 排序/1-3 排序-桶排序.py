## 桶排序(比如全是1000以内(不含1000)的数字)

import sys

# 输入与初始化
n = int(input())
li = list(map(int, sys.stdin.readline().split()))

# bucket_sort函数
def bucket_sort(li):
    buckets = [[] for i in range(20)]
    
    for num in li:
        buckets[int(num / 50)].append(num)   # 小数不能用//

    li_tem = []
    for bucket in buckets:
        bucket.sort()
        li_tem.extend(bucket)   # 是"extend"

    li[:] = li_tem  # 注意要这样替换
    return

# 运行输出
bucket_sort(li)
print(" ".join(str(x) for x in li))
