a=(int)(input())
b=(int)(input())
while b!=0:
    t=a
    a=b
    b=t%b
print a
