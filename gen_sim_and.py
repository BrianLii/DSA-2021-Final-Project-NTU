import sys
from dsa_mail.token import get_tokens


def count_hash(count):
    charlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    return charlist[count >> 6] + charlist[count & 0x3F]


if __name__ == "__main__":
    input_prefix = "test_data/mail"
    num_files = 10000
    log_freq = 500
    tokens = [None] * (num_files + 1)
    for i in range(1, num_files + 1):
        tokens[i] = set(get_tokens(f"{input_prefix}{i}"))

    for i in range(1, num_files + 1):
        for j in range(1, i + 1):
            print(count_hash(len(tokens[i] & tokens[j])), end="")
        if (i + 1) % log_freq == 0:
            print(f"{i + 1}/{num_files} completed", file=sys.stderr)
