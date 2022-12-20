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
#include <sys/time.h>

using namespace std;

#define MAX 80
#define PORT 8086
#define SA struct sockaddr

double socketCreationTime = 0;
double connectionTime = 0;
double sendingTime = 0;
double totalTime = 0;

long endTime(struct timeval start_time){
    long milli_time, seconds, useconds;
    struct timeval  end_time;
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec; //seconds
    useconds = end_time.tv_usec - start_time.tv_usec; //milliseconds
    milli_time = ((seconds) * 1000 + useconds/1000.0);
    return milli_time;
}

int sendAnswer(int studentID , char *answers){
    struct timeval start_time;

    gettimeofday(&start_time, NULL);

    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    //else
        //printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("3.142.122.252");
    servaddr.sin_port = htons(PORT);
    // connect the client socket to server socket

    socketCreationTime += endTime(start_time);

    gettimeofday(&start_time, NULL);
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0 ) {
        printf("connection %d with the server failed...\n", studentID);
        return 0;
    }

    connectionTime+=endTime(start_time);

    //else
        //printf("connected to the server..\n");

    gettimeofday(&start_time, NULL);
    int TotalSentBytes=0;
    while(TotalSentBytes < 620 ){
        int sentBytes = send(sockfd, answers, 620,0);
        if(sentBytes == -1) {
            cout<<"sending failed for " << studentID << " \n";
            return 0;
        }
        TotalSentBytes += sentBytes;
    }
    close(sockfd);
    sendingTime+=endTime(start_time);
    return 1;
}

int main()
{

    ifstream ifs = ifstream("questions.txt", ios_base::in);
    char buff[620];
    if (ifs.is_open() == true) {
        char c; int i = 0;
        while (ifs.get(c)) {
            buff[i] = c;
            i++;
        }
        ifs.close(); buff[i] = '\0';
    }


    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    for (int i=0;i<1;++i) {
        int id = i , j=5;
        while(id){
            buff[j] = (id%10)+'0';
            id=id/10;
            --j;
        }
        sendAnswer(i ,buff);

        //this_thread::sleep_for(chrono::milliseconds(1000));
    }
    totalTime += endTime(start_time);

    cout<<"total time = "<<totalTime/1000<<endl;
    cout<<"socket creation time = "<<socketCreationTime<<endl;
    cout<<"connection time = "<<connectionTime<<endl;
    cout<<"sending time = "<<sendingTime<<endl;

}
