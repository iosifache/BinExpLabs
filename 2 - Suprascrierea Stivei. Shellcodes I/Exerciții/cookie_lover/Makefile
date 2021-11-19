NO_STACK_SECURITY=-no-pie -fno-stack-protector -z execstack

all: clean cookie_lover.elf

cookie_lover.elf:
	gcc -m32 -mpreferred-stack-boundary=2 $(NO_STACK_SECURITY) -Wall cookie_lover.c -o cookie_lover.elf

clean:
	rm -rf cookie_lover.elf