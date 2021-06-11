print(
"""
int dp[10000][10000]=
""",end='')
print("{")
for i in range(10000):
    if(i!=0):print(',')
    print("{",end='')
    for j in range(10000):
        if(j!=0):print(',',end='')
        print(j,end='')
    print("}",end='')
print("};")
print(
"""
int main()
{
    return 0;
}
""")

