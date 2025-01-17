def to_c_array(data):
    return "{" + ",".join(data) + "}"


if __name__ == "__main__":
    source_name = "main.template.c"
    build_dir = ".build"
    with open(f"{build_dir}/num_tokens.txt", "r") as num_tokens:
        num_tokens = num_tokens.read().split()
        NUM_TOKENS_INIT = to_c_array(num_tokens)

    with open(f"{build_dir}/sender_receiver.txt", "r") as sender_receiver:
        ids = sender_receiver.read().split()
        sender_id, receiver_id = ids[::2], ids[1::2]
        SEND_IDS_INIT = to_c_array(sender_id)
        RECV_IDS_INIT = to_c_array(receiver_id)

    with open(f"{build_dir}/encoded_intersections.txt", "r") as sim_and:
        ENCODED_INTERSECTIONS = sim_and.read()
        ENCODED_INTERSECTIONS = ENCODED_INTERSECTIONS.replace("\\", "\\\\")

    with open(source_name, "r") as source:
        source = source.read()
        source = source.replace("NUM_TOKENS_INIT", NUM_TOKENS_INIT)
        source = source.replace("SEND_IDS_INIT", SEND_IDS_INIT)
        source = source.replace("RECV_IDS_INIT", RECV_IDS_INIT)
        source = source.replace("ENCODED_INTERSECTIONS", ENCODED_INTERSECTIONS)

    print(source)
