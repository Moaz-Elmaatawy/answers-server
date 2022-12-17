//
// Created by moaz on 12/15/22.
//
#include<iostream>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <vector>
#include <string>
#include <thread>

#define MAX 5000
#define PORT 8084
#define NUMBER_OF_STUDENTS 1000000
#define SA struct sockaddr

using namespace std;

vector<string>studentAnswers;
// Function designed for chat between client and server.
void func(int connfd)
{
    char buff[MAX];
    int n;
    for (int i=0;i<1000;++i) {
        bzero(buff, MAX);
        //cout<<"ready to read\n";
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        string s = string(buff);
        studentAnswers.push_back(s);

        if( s.size() != 612){
            cout<<s<<"\n\n";
        }

        this_thread::sleep_for(chrono::milliseconds(10));

    }
}

// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    //studentAnswers.resize(NUMBER_OF_STUDENTS);
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, reinterpret_cast<socklen_t *>(&len));
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
