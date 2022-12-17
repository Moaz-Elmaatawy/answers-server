//
// Created by moaz on 12/15/22.
//
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <fstream>
#include <thread>
#include <iostream>
using namespace std;

#define MAX 80
#define PORT 8084
#define SA struct sockaddr
void func(int sockfd)
{
    ifstream ifs = ifstream("questions.txt", ios_base::in);
    char buff[612];
    if (ifs.is_open() == true) {
        char c; int i = 0;
        while (ifs.get(c)) {
            buff[i] = c;
            i++;
        }
        ifs.close(); buff[i] = '\0';
    }

    cout<<string(buff).size()<<endl;

    for (int i=0;i<1000;++i) {
        write(sockfd, buff, sizeof(buff));
        //this_thread::sleep_for(chrono::milliseconds(1));
    }
}

int main()
{



    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
