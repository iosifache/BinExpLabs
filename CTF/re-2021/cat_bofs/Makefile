NO_STACK_SECURITY=-fno-stack-protector -z execstack

all: clean cat_bofs.elf

cat_bofs.elf:
	gcc -m32 -no-pie $(NO_STACK_SECURITY) -mpreferred-stack-boundary=2 -Wall cat_bofs.c -o cat_bofs.elf

clean:
	rm -rf cat_bofs.elf