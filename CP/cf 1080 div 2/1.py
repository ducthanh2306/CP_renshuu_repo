import sys,math
input = sys.stdin.readline
 
 
 
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    ok1 = 0
    ok2 = 0
    for x in a:
        if x == 1: ok1 = 1
        elif x == 67: ok2 = 1
    if  ok2: print("YES")
    else: print("NO")