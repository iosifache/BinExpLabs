all: clean build

build: libcheckflag.so flag-checker.elf

libcheckflag.so:
	gcc -m32 -c -fPIC library.c -o library.o
	gcc -m32 -shared library.o -o libcheckflag.so

flag-checker.elf:
	gcc -m32 -Wl,--no-as-needed source.c -zlazy -o flag-checker.elf -L. -lcheckflag -ldl 

clean:
	rm -f flag-checker.elf library.o libcheckflag.so