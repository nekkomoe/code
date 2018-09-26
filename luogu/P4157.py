n = int(input())
ans = 0
if n % 3 == 0:
	ans = 3 ** int(n / 3)
elif (n - 2) % 3 == 0:
	ans = 3 ** int((n - 2) / 3) * 2
else :
	ans = 3 ** int((n - 4) / 3) * 4

ans = str(int(ans))

print(len(ans))

if len(ans) < 100:
	print(ans)
else :
	print(ans[0 : 100])
