.PHONY: download
download:
	gdown '1-GPVynhpkj8gJseWnsxFBKn_YXyuxCDi'
	tar -xvzf mail_data.tar.gz
	mv test_data mail_data
	gdown '1-0ONMtK8khrYSwl7Xe8HM9i9vpnx94mI'
	unzip test_data.zip

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

.PHONY: test
test: main .test/validator
	./main < test_data/test.in | .test/validator

.PHONY: clean
clean:
	rm -rf .build .test main