#include <string.h> 
#include <stdio.h> 
#include <stdlib.h>

#define FIRST_SERVER "8.8.8.8"
#define SECOND_SERVER "8.8.4.4"

int main(){
    char ip[32];
    char command[64] = "ping -c 1 ";

    printf("[+] Google DNS IP you want to ping is: ");
    scanf("%31s", ip);

    if (strncmp(ip, FIRST_SERVER, sizeof(FIRST_SERVER) - 1) == 0 || strncmp(ip, SECOND_SERVER, sizeof(SECOND_SERVER) - 1) == 0){
        printf("[+] Ping output is:\n\n");

        strcat(command, ip);
        system(command);
    }
    else{
        printf("[!] Invalid IP address\n");
    }

} 