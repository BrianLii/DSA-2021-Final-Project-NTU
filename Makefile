num_tokens.txt: get_num_tokens.py
	python get_num_tokens.py > num_tokens.txt

sender_receiver.txt: get_sender_receiver.py
	python get_sender_receiver.py > sender_receiver.txt

encoded_intersections.txt: get_encoded_intersections.py
	python get_encoded_intersections.py > encoded_intersections.txt

main.c: main.template.c fill_template.py num_tokens.txt sender_receiver.txt encoded_intersections.txt
	python fill_template.py > main.c

main: main.c api.h
	gcc main.c -o main -O3 -std=c11 -w

validator/validator: validator/validator.cpp
	g++ validator/validator.cpp -o validator/validator -O3

.PHONY=run
run: main validator/validator
	./main < testdata/test.in | validator/validator
