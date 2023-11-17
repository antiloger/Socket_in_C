#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>

struct sockaddr_in* createTCPpv4Address(char *ip, int port);

int createTCPpv4Socket();

struct sockaddr_in* createTCPpv4Address(char *ip, int port){

    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}

int main(){

    int socketFD = createTCPpv4Socket();

    struct sockaddr_in *address = createTCPpv4Address("127.0.0.1", 2002);    

    int result = connect(socketFD, (struct sockaddr *)address, sizeof (*address));

    if(result == 0)
        printf("connect server");
    

    char* message;
    message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    char buffer[1024];
    recv(socketFD, buffer, 1024, 0);

    printf("Responce %s\n", buffer);


    return 0;
}

int createTCPpv4Socket(){

    return socket(AF_INET, SOCK_STREAM, 0);
}