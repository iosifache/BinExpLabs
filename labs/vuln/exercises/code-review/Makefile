all: clean build

build: build-line-appender build-ping-google-dns build-santa-letters

build-line-appender:
	gcc -m32 -Wall -no-pie -O0 line-appender.c -o line-appender.elf

build-ping-google-dns:
	gcc -m32 -Wall -no-pie -O0 ping-google-dns.c -o ping-google-dns.elf

build-santa-letters:
	gcc -m32 -Wall -no-pie -O0 santa-letters.c -o santa-letters.elf

clean:
	rm -f *.elf