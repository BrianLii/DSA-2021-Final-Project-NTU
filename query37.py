import re
def unique(tmp):
    return set(tmp)
def get_token_set(filename): # get all token in a mail
    f=open(filename, 'r')
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=re.findall('([A-Za-z0-9]+)',tmp)
    content=[i.lower() for i in tmp]
    content=unique(content)

    f=open(filename, 'r')
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=f.readline()
    tmp=tmp[9:]
    tmp=re.findall('([A-Za-z0-9]+)',tmp)
    subject=[i.lower() for i in tmp]
    subject=unique(subject)
    return subject | content
set1 = get_token_set("test_data/mail935")
'''
for i in range(1,10001):
    if i==935: continue;
    file = "test_data/mail"+str(i)
    set2 = get_token_set(file)
    union = set1 | set2
    intersection = set1 & set2
    threshold = len(intersection)/len(union)
    print(threshold,end=' ')
'''
for i in range(1,10001):
    if i==935: continue;
    file = "test_data/mail"+str(i)
    set2 = get_token_set(file)
    union = set1 | set2
    intersection = set1 & set2
    threshold = len(intersection)/len(union)
    if threshold > 0.110000000000:
        print(i,end=' ')