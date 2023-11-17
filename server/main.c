#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

struct sockaddr_in* createTCPpv4Address(char *ip, int port);

int createTCPpv4Socket();

struct sockaddr_in* createTCPpv4Address(char *ip, int port){

    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr = INADDR_ANY;
    return address;
}

int main(){
    
    int serverSocketFD = createTCPpv4Socket();
    struct sockaddr_in *serverAdress = createTCPpv4Address("", 2002);

    int result = bind(serverSocketFD, (struct sockaddr *)serverAdress, sizeof(*serverAdress));

    if(result == 0)
        printf("Socket was bound successfully!\n");
    
    int listenResult = listen(serverSocketFD, 10);

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress, &clientAddressSize);

    char buffer[1024];
    recv(clientSocketFD, buffer, 1024, 0);

    printf("Responce %s\n", buffer);

    close(serverSocketFD);
    close(clientSocketFD);
    return 0;

}

int createTCPpv4Socket(){

    return socket(AF_INET, SOCK_STREAM, 0);
}