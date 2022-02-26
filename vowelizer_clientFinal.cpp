//Ahmedh Shamsudeen 30121541

#include<stdio.h>
#include<time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include <string>
#include <cstring>
#include<stdlib.h>
#include<unistd.h> //close
#include <iostream>
using namespace std;

#define PORT_NUM 25510
#define SIZE 256
int num = 9000;

int main()
{
	int connection_fd = socket(AF_INET,SOCK_STREAM,0);
	if(connection_fd == -1) { perror("Failed to create socket"); return 1;}

    struct sockaddr_in connection_sa;
	memset(&connection_sa,0,sizeof(struct sockaddr_in));
	connection_sa.sin_family = AF_INET;
	connection_sa.sin_port = htons(PORT_NUM);
	connection_sa.sin_addr.s_addr = inet_addr("172.24.255.203");

	connect(connection_fd,(struct sockaddr*)&connection_sa,
			      sizeof(struct sockaddr_in));
	if(connection_fd == -1) { perror("Failed to connect"); return 1;}

	
    string input;
    
 

	while (1){
	cout << "Please choose from the following selections:\n\t1 - Devowel a message\n\t2 - Envowel a message\n\t0 - Exit program\nYour desired menu selection? ";
	
    getline(cin, input);
    

    if (input == "1"){
        //SENT WITH TCP
        send(connection_fd,"1",sizeof("1"),0);
        printf("Enter message to devowel: ");

        string inputOne;

        getline(std::cin, inputOne);

        int n = inputOne.length();
        char buff[SIZE];
        strcpy(buff, inputOne.c_str());
	    send(connection_fd,buff,SIZE,0);
        recv(connection_fd,buff,SIZE,0);
        printf("Non-vowels sent by server using TCP: %s\n\n",buff);

        //memset(&servaddr, 0, sizeof(servaddr));
        memset(buff ,0 , SIZE);
    int sockfd;
    char buffer[SIZE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
    //setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(struct timeval));
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(num);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    num++;
      
    int z, len;
      
    sendto(sockfd, (const char *)hello, strlen(hello),
        0, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    
          
    z = recvfrom(sockfd, (char *)buffer, SIZE, 
                0, (struct sockaddr *) &servaddr,
                (socklen_t *)&len);

    /*if(z == -1)
	{
		perror("Packet lost\n");		
	}   */             
    buffer[n] = '\0';
    
  
                             

        


        printf("Vowels sent by server using UDP: %s\n\n",buffer);

        //close(connection_fd);
    }
    else if (input == "2"){
        //SENT with TCP
        send(connection_fd,"2",sizeof("1"),0);
        printf("Enter non-vowel part of message to envowel: ");
        string non_Vowel;
        getline(std::cin, non_Vowel);
        int n = non_Vowel.length();
        char buff[SIZE];
        strcpy(buff, non_Vowel.c_str());
	    send(connection_fd,buff,SIZE,0);
        

        //Must be done in UDP
        printf("Enter vowel part of message to envowel: ");
        string Vowel;
        getline(std::cin, Vowel);
        int k = Vowel.length();
        char buff1[SIZE];
        strcpy(buff1, Vowel.c_str());
	    //send(connection_fd,buff1,SIZE,0);//send using UDP

        int sockfd;
    char buffer[SIZE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
    //setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(struct timeval));
    
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(num);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    num++;  
    int  len;
      
    sendto(sockfd, buff1, SIZE,
        0, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    
          
    /*z = recvfrom(sockfd, (char *)buffer, SIZE, 
                0, (struct sockaddr *) &servaddr,
                (socklen_t *)&len);*/
    //buffer[n] = '\0';

        memset(buff1 ,0 , SIZE);
        
        recv(connection_fd,buff1,SIZE,0);
        printf("Server sent message using TCP: '%s'\n" , buff1);

        //close(connection_fd);
    }
    else{break;}
    

    
    }
	close(connection_fd);	

	return 0;
}
