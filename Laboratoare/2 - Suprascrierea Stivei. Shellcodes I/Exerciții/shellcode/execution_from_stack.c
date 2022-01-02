int main(int argc, char **argv) {
    const char shellcode[] = "";

    void (*function)();
    function = (void (*)())shellcode;
    (void)(*function)();

    return 0;
}