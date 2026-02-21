h, w, k = list(map(int, input().split()))
c = list(map(int, input().split()))
c.sort()
gaps = [c[i] - c[i-1] for i in range(1, k)]
def check(x):
    currow = 1
    for gap in gaps:
        if gap < x:
            currow += x - gap
            if currow > h:
                return False
    return True
lo = 1
hi = h + w
ans = -1
while lo <= hi:
    mid = int((lo + hi) / 2)
    if check(mid):
        lo = mid + 1
        ans = mid
    else:
        hi = mid - 1
print(ans)
