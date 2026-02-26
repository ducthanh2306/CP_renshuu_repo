t = int(input())
for _ in range(t):
	n,m,d = map(int, input().split())
	max_one_tower = (d // m) + 1
	if max_one_tower == 1:
		print(n)
	else:
		print((n + max_one_tower - 1) // (max_one_tower))