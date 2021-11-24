NO_STACK_SECURITY=-fno-stack-protector -z execstack

all: clean cookie_lover.elf

cookie_lover.elf:
	gcc -m32 -no-pie $(NO_STACK_SECURITY) -mpreferred-stack-boundary=2 -Wall cookie_lover.c -o cookie_lover.elf

clean:
	rm -rf cookie_lover.elf