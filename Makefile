all: assembler.c opcode.c
	gcc -o main assembler.c opcode.c -I .

run:
	./main

clean:
	rm -f main
	rm -f t

test: test.c opcode.c
	gcc -o t test.c opcode.c -I .
	./t
	rm -f t
