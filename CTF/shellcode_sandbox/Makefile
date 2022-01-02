all: clean build

build:
	gcc -m32 -no-pie -Xlinker -Tdata=0x44444444 source.c -o shellcode_sandbox.elf

clean:
	rm -f shellcode_sandbox.elf