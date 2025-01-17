import sys
from dsa_mail.name import get_sender_receiver, name_to_id

if __name__ == "__main__":
    input_prefix = "mail_data/mail"
    num_files = 10000
    log_freq = 1000
    names = dict()
    for i in range(1, num_files + 1):
        sender, receiver = get_sender_receiver(f"{input_prefix}{i}")
        sender = name_to_id(sender, names)
        receiver = name_to_id(receiver, names)
        print(sender, receiver)
        if i % log_freq == 0:
            print(f"{i}/{num_files} completed", file=sys.stderr)
    print(f"number of names: {len(names)}", file=sys.stderr)
