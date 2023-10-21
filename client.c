#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 5950

void handle_connection(int fd);

void main()
{
    int client;
    struct sockaddr_in serverAddress;
    struct sockaddr server;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if ((client = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error while creating server socket.");
        exit(EXIT_FAILURE);
    }


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);           
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

    if ((connect(client, (struct sockaddr *)&serverAddress, sizeof(serverAddress))) == -1)
    {
        perror("Error while connecting to server.");
        close(client);
        exit(1);
    }

    handle_connection(client);
    close(client);
}


void handle_connection(int sockFD)
{
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;

    char tempBuffer[1000];

    
    while(1){
        bzero(readBuffer, 1000);
        readBytes = read(sockFD, readBuffer, sizeof(readBuffer));
        if(strcmp(readBuffer, "Invalid Choice.\n")==0)break;

        else if (readBytes == -1)
            perror("Error while reading from client socket.");
        else if (readBytes == 0)
            printf("No error received from server! Closing the connection to the server now.\n");
        
        else
        {
            bzero(writeBuffer, 1000);

            write(1, readBuffer, sizeof(readBuffer));
            int i=0;
            while(1){
                char c;
                read(0, &c, 1);
                if(c=='\n')break;
                writeBuffer[i]=c;
                i++;
            }

            writeBuffer[i]='\0';
            writeBytes = write(sockFD, writeBuffer, strlen(writeBuffer));

            if (writeBytes == -1)
            {
                perror("Error while writing to client socket!");
                printf("Closing the connection to the server now!\n");
                break;
            }
        }
    }

    close(sockFD);

}


