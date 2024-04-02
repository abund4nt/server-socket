#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <pthread.h>

#define MAX 80 
#define PORT 8010
#define SA struct sockaddr 

void *handle_client(void *arg) {
    int connfd = *((int *)arg);
    char buff[MAX]; 
    int n; 
 
    for (;;) { 
        bzero(buff, MAX); 
        n = read(connfd, buff, sizeof(buff)); 
        if (n == 0) { 
            printf("[CONNECTION] - Client disconnected\n");
            break;
        }
    
        printf("%s", buff); 
        
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
    close(connfd);
    pthread_exit(NULL);
} 


// Driver function 
int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
    pthread_t tid;

    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("[ERROR] - Socket creation failed.\n"); 
        exit(0); 
    } 
    else
        printf("[SERVER] - Socket successfully created.\n"); 
    bzero(&servaddr, sizeof(servaddr)); 

    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 

    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("[ERROR] - Socket bind failed.\n"); 
        exit(0); 
    } 
    else
        printf("[SERVER] - Socket successfully binded.\n"); 

    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("[ERROR] - Listen failed port as used.\n"); 
        exit(0); 
    } 
    else
        printf("[SERVER] - Server listening in port %d.\n", PORT); 

    while (1) {
        len = sizeof(cli); 

        // Accept the data packet from client and verification 
        connfd = accept(sockfd, (SA*)&cli, &len); 
        if (connfd < 0) { 
            printf("[ERROR] - Server accept the client failed...\n"); 
            exit(0); 
        } 
        else
            printf("\n[CONNECTION] - A new client is connected\n"); 

        // Create a new thread to handle the client connection
        pthread_create(&tid, NULL, handle_client, &connfd);
    }

    close(sockfd); 
    return 0;
}
