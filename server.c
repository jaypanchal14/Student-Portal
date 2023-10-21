#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string.h> 
#include <stdbool.h> 
#include <stdlib.h> 

#include "auth.h"
#include "student.h"
#include "faculty.h"
#include "admin.h"

#define PORT 5950

void handle_connection(int fd);

void main()
{
    int server, client;
    struct sockaddr_in serverAddress, clientAddress;

    if((server = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error while creating server socket");
        exit(EXIT_FAILURE);
    }

    int enable = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY); 

    if( bind(server, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1){
        perror("Error while binding to server socket");
        exit(EXIT_FAILURE);
    }

    if(listen(server, 10) == -1){
        perror("Error while listening for connections from server");
        close(server);
        exit(EXIT_FAILURE);
    }

    int clientSize;
    while (1){
        clientSize = (int)sizeof(clientAddress);
        client = accept(server, (struct sockaddr *)&clientAddress, &clientSize);
        if (client == -1){
            perror("Error while aceepting to client connection");
            close(server);
        }
        else{
            if (!fork())
            {
                // Child process
                handle_connection(client);
                close(client);
                break;
            }
        }
    }
    close(server);
}

void handle_connection(int cfd)
{
    printf("Client with fd : %d has connected to the server.\n", cfd);
    bool flag = 0;
    
    while(1){
        char readBuffer[1000], writeBuffer[1000];
        ssize_t readBytes, writeBytes;
        int userChoice;

        strcpy(writeBuffer, ".................Welcome Back to Academia (Student Portal).................\nEnter your role  :  1. Faculty 2. Student 3. Admin 4. Exit\n");

        writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1){
            perror("Error while sending first prompt to the user.");
        }
        else{
            bzero(readBuffer, 1000);
            memset(readBuffer, 0, sizeof(readBuffer));
            readBytes = read(cfd, readBuffer, sizeof(readBuffer));            

            if (readBytes == -1){
                perror("Error while reading from client");

            }else if (readBytes == 0){
                printf("No data was sent by the client");

            }else{
                userChoice = atoi(readBuffer);
                switch (userChoice){
                case 1:
                    facultyMenu(cfd);
                    break;
                case 2:
                    studentMenu(cfd);
                    break;
                case 3:
                    adminMenu(cfd);
                    break;
                default:
                    memset(writeBuffer, 0, sizeof(writeBuffer));
                    strcpy(writeBuffer, "Invalid Choice.\n");
                    write(cfd, writeBuffer, strlen(writeBuffer));
                    flag = 1;
                    break;
                }
            }
        }
        if(flag){
            break;
        }
    }
    printf("Terminating connection to client.\n");
}
