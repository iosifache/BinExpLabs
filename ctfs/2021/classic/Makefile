all: clean build

build:
	gcc -m32 -fno-stack-protector -no-pie source.c -o classic.elf

clean:
	rm -f classic.elf