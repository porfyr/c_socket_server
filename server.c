#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
// #include <netinet/in.h>
#include <error.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ERROR       -1
#define MAX_CLIENTS 2
#define MAX_DATA    1024

char * message_filter(char* input);

int main(int argc, char **argv)
{
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sock;
    int new;
    int sockaddr_len = sizeof(struct sockaddr_in);
    char data_len;
    char data[MAX_DATA];

    if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)         // Ставлю сокет
    {
        perror("server socket: ");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    if ( (bind(sock, (struct sockaddr *)&server, sockaddr_len)) == ERROR )
    {
        perror("bind: ");
        exit(-1);
    }

    if ( (listen(sock, MAX_CLIENTS)) == ERROR)
    {
        perror("listen");
        exit(-1);
    }

    while (1)                       // Кустарне прослуховування порта на сокеті
    {
        if ( (new = accept(sock, (struct sockaddr *)&client, &sockaddr_len)) == ERROR)
        {
            perror("accept");
            exit(-1);
        }

        printf("New Client connected from port № %d and IP %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
        // send(new, "3xx", 4, 0);

        data_len = 1;
        
        while (data_len)
        {
            data_len = recv(new, data, MAX_DATA, 0);
            if (strcmp(data, "s\n") == 0)
            {
                printf("OMG\n");
            }
            if (data_len >= 2)
            {
                // printf("lol: '%s'\n", data);
                data[data_len-1] = (char)0;
                //data[data_len-2] = (char)0;
                data_len --;

                if ( strcmp(data, "stop") == 0 || strcmp(data, "close") == 0)
                {
                    // strcpy(data, "ok\n");
                    // data_len = 4;
                    // send(new, data, data_len, 0);
                    printf("Client asked for stop\n");
                    exit(0);
                }
                else if ( strcmp(data, "dai cod") == 0 )
                {
                    strcpy(data, "2xx\n");
                    data_len = 5;
                    send(new, data, data_len, 0);
                    data[data_len] = '\0';
                    printf("Sent code: %s\n", "2xx");
                }
                else if ( strcmp(data, "nu daai") == 0 )
                {
                    strcpy(data, "3xx\n");
                    data_len = 5;
                    send(new, data, data_len, 0);
                    data[data_len] = '\0';
                    printf("Sent code: %s\n", "3xx");
                }
                else
                {
                    printf("Got msg: %s\n", data);
                    send(new, data, data_len, 0);
                    printf("Echoed msg: '%s'\n", data);
                }
            }
        }

        printf("Client disconnected\n");

        close(new);
    }

    return 0;
}