all: clean build

build: build_packed build_stripped

build_packed:
	gcc -m32 -no-pie -static -fstack-protector-all source.c -o fortress.static.elf
	upx fortress.static.elf -o fortress.packed.elf

build_stripped:
	gcc -m32 -no-pie -fstack-protector-all source.c -o fortress.elf
	strip fortress.elf -o fortress.stripped.elf

clean:
	rm -f fortress.*