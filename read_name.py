import re
def unique(tmp):
    return list(set(tmp))
def get_name(filename):
    f=open(filename, 'r')
    tmp=f.readline()
    A=tmp[6:-1]
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    B=tmp[4:-1]
    return A,B
for i in range(10000):
    if(i%1000==0):print(i)
    A,B=get_name('test_data/mail'+str(i+1))
