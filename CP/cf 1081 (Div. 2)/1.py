t = int(input())
def block(s):
    cnt = 1
    for i in range(1,len(s)):
        if s[i] != s[i - 1]:
            cnt +=1
    return cnt
def exist_dup(s):
    cnt = 0
    for i in range(1,len(s)):
        if s[i] == s[i - 1]:
            return True
    return False
for _ in range(t):
    n = int(input())
    s = input()
    if s[-1] != s[0] and exist_dup(s):
        print(block(s) + 1)
    else:
        print(block(s))

    