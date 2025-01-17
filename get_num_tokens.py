import sys
from dsa_mail.token import get_num_tokens

if __name__ == '__main__':
    input_prefix = 'mail_data/mail'
    num_files = 10000
    log_freq = 1000
    all_tokens = []
    for i in range(1, num_files + 1):
        print(get_num_tokens(f'{input_prefix}{i}'), end=' ')
        if i % log_freq == 0:
            print(f'{i}/{num_files} completed', file=sys.stderr)
