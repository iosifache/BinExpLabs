# Dezactivează canariile
LOW_STACK_SECURITY=-fno-stack-protector

all: clean build

build:
	gcc -m32 -no-pie $(LOW_STACK_SECURITY) source.c -o multifunctional.elf

clean:
	rm -f multifunctional.elf