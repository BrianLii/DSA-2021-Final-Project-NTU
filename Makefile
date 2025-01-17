.build:
	mkdir -p .build

.build/num_tokens.txt: get_num_tokens.py | .build
	python get_num_tokens.py > .build/num_tokens.txt

.build/sender_receiver.txt: get_sender_receiver.py | .build
	python get_sender_receiver.py > .build/sender_receiver.txt

.build/encoded_intersections.txt: get_encoded_intersections.py | .build
	python get_encoded_intersections.py > .build/encoded_intersections.txt

main.c: main.template.c fill_template.py .build/num_tokens.txt .build/sender_receiver.txt .build/encoded_intersections.txt
	python fill_template.py > main.c

main: main.c api.h
	gcc main.c -o main -O3 -std=c11 -w

.test:
	mkdir -p .test

.test/validator: validator.cpp | .test
	g++ validator.cpp -o .test/validator -O3

.PHONY: run
run: main .test/validator
	./main < testdata/test.in | .test/validator
