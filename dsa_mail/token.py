import re

def unique(tmp):
    return sorted(list(set(tmp)))

def get_tokens(filename, token_regex=r'[A-Za-z0-9]+'):
    tokens = []
    with open(filename, "r") as file:
        for i in range(7):
            line = file.readline()
            if i == 3:
                tokens.extend(re.findall(token_regex, line[9:]))
            elif i == 6:
                tokens.extend(re.findall(token_regex, line))
    tokens = [token.lower() for token in tokens]
    return unique(tokens)

def get_tokens_size(filename, token_regex=r'[A-Za-z0-9]+'):
    return len(get_tokens(filename, token_regex))