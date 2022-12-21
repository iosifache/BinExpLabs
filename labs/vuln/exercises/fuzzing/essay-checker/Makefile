# Marchează stiva ca fiind executabilă
NO_STACK_SECURITY=-z execstack -fno-stack-protector

all: clean build

build:
	gcc -m32 -no-pie -Wall $(NO_STACK_SECURITY) essay-checker.c -o essay-checker.elf

clean:
	rm -f essay-checker.elf