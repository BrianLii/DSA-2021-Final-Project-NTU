def to_c_array(data):
    return "{" + ",".join(data) + "}"


if __name__ == "__main__":
    source_name = "main.c"

    with open("token_sizes.txt", "r") as token_sizes:
        token_sizes = token_sizes.read().split()
        TOKEN_SET_SIZE_INIT = to_c_array(token_sizes)

    with open("sender_receiver.txt", "r") as sender_receiver:
        ids = sender_receiver.read().split()
        sender_id, receiver_id = ids[::2], ids[1::2]
        FROM_HASH_INIT = to_c_array(sender_id)
        TO_HASH_INIT = to_c_array(receiver_id)

    with open("sim_and.txt", "r") as sim_and:
        SIM_S_INIT = sim_and.read()

    with open(source_name, "r") as source:
        source = source.read()
        source = source.replace("TOKEN_SET_SIZE_INIT", TOKEN_SET_SIZE_INIT)
        source = source.replace("FROM_HASH_INIT", FROM_HASH_INIT)
        source = source.replace("TO_HASH_INIT", TO_HASH_INIT)
        source = source.replace("SIM_S_INIT", SIM_S_INIT)

    print(source)
