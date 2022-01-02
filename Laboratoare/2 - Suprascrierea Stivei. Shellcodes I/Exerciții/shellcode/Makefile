# Marcheaza stiva ca fiind executabila
NO_STACK_SECURITY=-z execstack

all: clean execution_from_stack.elf execution_with_mprotect.elf

get_shellcode:
	rm -f shellcode.bin
	nasm shellcode.S -o shellcode.bin
	hexdump -v -e '"\\" 1/1 "x%02x"' shellcode.bin

execution_from_stack.elf:
	gcc -m32 -no-pie $(NO_STACK_SECURITY) execution_from_stack.c -o execution_from_stack.elf

execution_with_mprotect.elf:
	gcc -m32 -no-pie execution_with_mprotect.c -o execution_with_mprotect.elf

clean:
	rm -f shellcode.bin execution_from_stack.elf execution_with_mprotect.elf