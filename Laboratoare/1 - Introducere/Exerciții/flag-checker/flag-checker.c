#include "dlfcn.h"
#include "stdio.h"
#include "string.h"

#define LIBRARY_NAME "libcheckflag.so"
#define FUNCTION_NAME "check_flag"

int main(int argc, char *argv[]) {

    void *handle;
    int (*check_flag)(char *);
    char *provided_flag;
    int success;

    if (argc != 2) {
        printf("A flag needs to be provied as an argument!\n");

        return 1;
    }
    provided_flag = argv[1];

    handle = dlopen(LIBRARY_NAME, RTLD_LOCAL | RTLD_LAZY);
    if (handle == NULL) {
        printf("Cannot find the library needed to verify the flag, " LIBRARY_NAME "!\n");

        return 1;
    }
    *(void **)(&check_flag) = dlsym(handle, FUNCTION_NAME);

    success = (*check_flag)(provided_flag);
    if (success) {
        printf("\nCongrats, you get the flag!\n");

        return 0;
    } else {
        return 1;
    }

    return 0;

}