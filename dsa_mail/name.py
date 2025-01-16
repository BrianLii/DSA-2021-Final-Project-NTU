def name_to_id(name, names):
    if name in names.keys(): return names[name]
    names[name] = len(names)
    return names[name]

def get_sender_receiver(filename):
    with open(filename, 'r') as file:
        for i in range(5):
            line = file.readline()
            if i == 0: sender = line[6:-1]
            elif i == 4: receiver = line[4:-1]
    return sender, receiver