#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define DATA argv[2]//"mega lang streng kommer der her"//argv[2]//"Hello socket world"

int main(int argc, char *argv[])
{

    /* Variables */
    int sock; // Get return value of sock function
    struct sockaddr_in server; //
    struct hostent *hp;
    char buff[1024]; // Buffer to return the data


    /* Create socket */
    // AF_INET means that we are creating TCP/IP scoket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    //server.sin_addr.s_addr = INADDR_ANY;
    //server.sin_port = htons(5000);

    hp = gethostbyname(argv[1]);
    if(hp == 0)
    {
        perror("gethostbyname failed");
        close(sock);
        exit(1);
    }

    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_port = htons(5000);

    if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        perror("connect failed");
        close(sock);
        exit(1);
    }

    if(send(sock, DATA, sizeof(DATA), 0) < 0)
    {
        perror("send failed");
        close(sock);
        exit(1);
    }

    printf("Sent %s\n", DATA);
    close(sock);

    return 0;

}
