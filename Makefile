main: main.c api.h
	gcc main.c -o main.exe -O3 -std=c11 -w

validator/validator: validator/validator.cpp
	g++ validator/validator.cpp -o validator/validator -O3

.PHONY=run
run: main validator/validator
	./main.exe < testdata/test.in | validator/validator
