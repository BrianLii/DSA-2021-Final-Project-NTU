import re
import sys

def unique(tmp):
    return sorted(list(set(tmp)))


def get_token_set(filename, token_regex=r"[A-Za-z0-9]+"):
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


def get_all_tokens(
    input_prefix="test_data/mail",
    num_files=10000,
    log_freq=1000,
):
    num_files = 10000
    all_tokens = []
    for i in range(1, num_files + 1):
        all_tokens.extend(get_token_set(f"{input_prefix}{i}"))
        if i % log_freq == 0:
            print(f"{i}/{num_files} completed", file=sys.stderr)
    all_tokens = unique(all_tokens)
    return all_tokens


if __name__ == "__main__":
    print(*get_all_tokens())