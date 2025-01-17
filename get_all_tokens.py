import sys
from dsa_mail.token import get_tokens, unique

if __name__ == '__main__':
    input_prefix = 'mail_data/mail'
    num_files = 10000
    log_freq = 1000
    all_tokens = []
    for i in range(1, num_files + 1):
        all_tokens.extend(get_tokens(f'{input_prefix}{i}'))
        if i % log_freq == 0:
            print(f'{i}/{num_files} completed', file=sys.stderr)
    all_tokens = unique(all_tokens)
    print(*all_tokens)
