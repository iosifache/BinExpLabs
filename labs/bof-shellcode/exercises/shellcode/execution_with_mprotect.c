#include <string.h>
#include <sys/mman.h>

const char shellcode[] = "";

int main(int argc, char **argv) {
    void *mem = mmap(0, sizeof(shellcode), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    memcpy(mem, shellcode, sizeof(shellcode));
    mprotect(mem, sizeof(shellcode), PROT_READ | PROT_WRITE | PROT_EXEC);

    void (*function)();
    function = (void (*)())mem;
    (void)(*function)();

    munmap(mem, sizeof(shellcode));

    return 0;
}