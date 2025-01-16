def to_c_array(data):
    return "{" + ",".join(data) + "}"


if __name__ == "__main__":
    source_name = "main.c"

    token_sizes_filename = "token_sizes.txt"
    with open(token_sizes_filename, "r") as token_sizes:
        token_sizes = token_sizes.read().split()
        TOKEN_SET_SIZE_INIT = to_c_array(token_sizes)

    sender_receiver_filename = "sender_receiver.txt"
    with open(sender_receiver_filename, "r") as sender_receiver:
        ids = sender_receiver.read().split()
        sender_id, receiver_id = ids[::2], ids[1::2]
        FROM_HASH_INIT = to_c_array(sender_id)
        TO_HASH_INIT = to_c_array(receiver_id)

    with open(source_name, "r") as source:
        source = source.read()
        source = source.replace("TOKEN_SET_SIZE_INIT", TOKEN_SET_SIZE_INIT)
        source = source.replace("FROM_HASH_INIT", FROM_HASH_INIT)
        source = source.replace("TO_HASH_INIT", TO_HASH_INIT)

    print(source)
