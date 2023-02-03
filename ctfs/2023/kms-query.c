#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    void *handle;
    char request_format[128];
    char username[32];
    char key[32];
    char *request;
    char *request_info;
    char *logging;
    char *query_result;

    srand(time(NULL));

    printf("[i] This is a proprietary KMS client. All your actions will be logged. Press ENTER to continue.");
    getchar();

    printf("[i] The recommended request format is \"{'action': 'get_vault', 'username': '%%s', 'key': '%%s'}\".\n");
    printf("[?] Enter the request format you want to use: ");
    fgets(request_format, 127, stdin);
    if (request_format[strlen(request_format) - 1] == '\n')
        request_format[strlen(request_format) - 1] = '\0';

    printf("[?] Enter your username: ");
    scanf("%31s", username);

    printf("[?] Enter your key: ");
    scanf("%31s", key);

    asprintf(&request, request_format, username, key);
    asprintf(&request_info, "[i] The built query is \"%s\".\n", request);
    printf(request_info);

    query_result = execute_request(request);

    printf("[+] The KMS query result is: \"%s\".\n", query_result);

    asprintf(&logging, "echo %s >> /tmp/%s", key, username);
    system(logging);

    free(request);
    free(request_info);

    return 0;
}