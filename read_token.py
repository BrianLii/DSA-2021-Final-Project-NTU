import re


def unique(tmp):
    return list(set(tmp))


def get_token_set(filename):  # get all token in a mail
    f = open(filename, "r")
    tmp = f.readline()
    tmp = f.readline()
    tmp = f.readline()
    tmp = f.readline()
    tmp = f.readline()
    tmp = f.readline()
    tmp = f.readline()
    tmp = re.findall("([A-Za-z0-9]+)", tmp)
    content = [i.lower() for i in tmp]
    content = unique(content)

    f = open(filename, "r")
    tmp = f.readline()
    tmp = f.readline()
    tmp = f.readline()
    tmp = f.readline()
    tmp = tmp[9:]
    tmp = re.findall("([A-Za-z0-9]+)", tmp)
    subject = [i.lower() for i in tmp]
    subject = unique(subject)
    return unique(subject + content)


def collect_all_token():
    all_token = []
    for i in range(1, 10001):
        name = "test_data/mail" + str(i)
        all_token = all_token + get_token_set(name)
        if i % 200 == 0:
            print(f"{i}/10000")
            all_token = list(set(all_token))
    all_token = unique(all_token)
    w = open("alltoken.txt", "w")
    for i in all_token:
        w.write(f"{i},")
    return all_token


collect_all_token()
f = open("alltoken.txt", "r")
all_token = f.readline().split(",")
