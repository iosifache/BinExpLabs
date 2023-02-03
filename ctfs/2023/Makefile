all: clean build

build: libkms.a kms-query.elf

kms-query.elf:
	gcc -m32 -fno-stack-protector kms-query.c -L. -lkms -o kms-query.elf

libkms.a:
	gcc -m32 -fno-stack-protector -c libkms.c -o libkms.o
	ar -rc libkms.a libkms.o

clean:
	rm -f kms-query.elf libkms.o libkms.a