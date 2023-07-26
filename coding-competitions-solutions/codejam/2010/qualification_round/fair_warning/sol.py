from math import gcd

C = int(input())
for case_num in range(1, C + 1):
  t = list(map(int, input().split()))[1:]
  m = min(t)
  t = [i - m for i in t]
  d = gcd(*t)
  print('Case #{}: {}'.format(case_num, (d - m % d) % d))
