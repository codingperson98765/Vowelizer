//Ahmedh Shamsudeen 



#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h> //fork
#include<string.h>
#include<unistd.h>
#include<time.h>
#include <iostream>
#include <string>
using namespace std;


#define PORT_NUM 25510
#define PORT_UDP 9000
#define SIZE 256
#define HELLO "Hello world\n"
#define ADVANCED 1 //1 is advanced anything else is simple
int num = 9000;


void echo(int);
void echoSimple(int fd);



int main()
{
	printf("Server Running \n");
	

	//Create Socket for incomming TCP connections
	int listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    

    
	int connection_fd;

	//Check to see if we failed
	if(listener_fd == -1){ perror("Failed to create socket file discriptor"); return EXIT_FAILURE; }

	//Initialize the socket take to allow connection from any IP on PORT_NUM
	//Note that there are may flags in this magic block and memset make sure 
	//all are off for you, until we turn the ones we want on.
	struct sockaddr_in listener_sa;
	memset(&listener_sa,0,sizeof(struct sockaddr_in));
	listener_sa.sin_family = AF_INET;
	listener_sa.sin_port = htons(PORT_NUM);
	listener_sa.sin_addr.s_addr = htonl(INADDR_ANY);
	//listener_sa.sin_addr = 0;
	
	
	if(bind(listener_fd,(struct sockaddr*) &listener_sa, 
			    sizeof(struct sockaddr_in)) == -1)
	{
		perror("Failed to bind socket\n");
		return EXIT_FAILURE;
	}
	
	//Mark socket as a passive socket i.e one that will accept connections
	//Set the queue length of incoming connections to be 5
	if(listen(listener_fd,5) == -1) { return EXIT_FAILURE; }
	
	//Will never exit this while loop
	//Only when accept errors
	//connection_fd is the fd for the inccoming socket
	while((connection_fd = accept(listener_fd,NULL,NULL)) != -1)
	{
		//This code block is very specifically designed
		//google it if you do not know what it does or why
		int pid = fork();
		if(pid == 0) //Child
		{
            if (ADVANCED == 1){echo(connection_fd);}
			else if(ADVANCED !=1){echoSimple(connection_fd);}
			close(connection_fd);
			exit(EXIT_SUCCESS);
		}
		else if(pid != 0)//Parrent
		{
			close(connection_fd);
		}
		else//Error
		{
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

//Gets data from the client then echos it back
//Then returns form exection.
void echo(int fd)
{
	char buff[SIZE], blankSpace = ' ',i;
    while(1){
    memset(buff ,0 , SIZE);
    recv(fd,buff,SIZE,0);
    

    if (strchr(buff, '1') != NULL)
    {
        recv(fd,buff,SIZE,0);
        size_t ArraySize = sizeof(buff)/sizeof(buff[0]);
        char constantArray[ArraySize +1], vowelArray[ArraySize + 1];
        size_t destination_size = sizeof (constantArray);
        

        strncpy(constantArray, buff, destination_size); 
        strncpy(vowelArray, buff, destination_size); 
         

        
        
    for(i=0; buff[i]!='\0'; i++)
    {
        if(buff[i]=='a' || buff[i]=='e' || buff[i]=='i' || buff[i]=='o'
           || buff[i]=='u' || buff[i]=='A' || buff[i]=='E' || buff[i]=='I'
           || buff[i]=='O' || buff[i]=='U')
        {
            constantArray[i] = blankSpace;
        }
    }
    
    for(i=0; buff[i]!='\0'; i++)
    {
        if(buff[i]!='a' && buff[i]!='e' && buff[i]!='i' && buff[i]!='o'
           && buff[i]!='u' && buff[i]!='A' && buff[i]!='E' && buff[i]!='I'
           && buff[i]!='O' && buff[i]!='U')
        {
            
            vowelArray[i] = blankSpace;
        }
    }
    
       

        send(fd,constantArray,SIZE,0);
        //send(fd,vowelArray,SIZE,0);
        int k = 0,pos = 0 ;
        char dup[SIZE];
        memset(dup ,0 , SIZE);
        for(int i = 0; vowelArray[i] != '\0'; i++){
        
        if (vowelArray[i] == ' '){
            k++;
                }
        else if (vowelArray[i] != ' ' && vowelArray[i] != '\0'){
            dup[pos] = k + '0';
            pos++;
            dup[pos] = vowelArray[i];
            pos++;
            k= 0;
        }
    //strncpy(vowelArray, dup, destination_size);    
    }

        

        int sockfd;
    char buffer[SIZE];
    //char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

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
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(num);

    num++;

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);  //len is value/resuslt    

    n = recvfrom(sockfd, (char *)buffer, SIZE,
                0, ( struct sockaddr *) &cliaddr,
                (socklen_t*)&len);
    buffer[n] = '\0';
    /*if(n == -1)
	{
		perror("Packet lost\n");		
	}*/                
    
    sendto(sockfd, dup, SIZE,
        0, (const struct sockaddr *) &cliaddr,
            len);
  
    }
    else if (strchr(buff, '2') != NULL)
    {
        memset(buff ,0 , SIZE);
        int vowelCount = 0, constantCount = 0;

        recv(fd,buff,SIZE,0);
        for(int i=0; buff[i]!='\0'; i++)
    {
        if(buff[i]!='a' && buff[i]!='e' && buff[i]!='i' && buff[i]!='o'
           && buff[i]!='u' && buff[i]!='A' && buff[i]!='E' && buff[i]!='I'
           && buff[i]!='O' && buff[i]!='U' && buff[i] != ' ')
        {
            
            constantCount = i;
        }
    }
        //send(fd,buff,SIZE,0);
        

        size_t ArraySize = sizeof(buff)/sizeof(buff[0]);
        char constantArray[ArraySize +1];
        size_t destination_size = sizeof (constantArray);
        

        strncpy(constantArray, buff, destination_size); 
        memset(buff ,0 , SIZE);
        //recv(fd,buff,SIZE,0);//WILL BE SWITCHED TO UDP RECVFROM

         int sockfd;
    char buffer[SIZE];
    //char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

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
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(num);

    num++;

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);  //len is value/resuslt    

    n = recvfrom(sockfd, buff, SIZE,
                0, ( struct sockaddr *) &cliaddr,
                (socklen_t*)&len);
    buff[n] = '\0';
                    
    int y =0;
    char dup[SIZE];
    memset(dup ,0 , SIZE);
    for(int i = 0; buff[i] != '\0'; i++){
        if(buff[i]!='a' && buff[i]!='e' && buff[i]!='i' && buff[i]!='o'
           && buff[i]!='u' && buff[i]!='A' && buff[i]!='E' && buff[i]!='I'
           && buff[i]!='O' && buff[i]!='U' && buff[i]!= ' '){
               for(int k = 0; k < (buff[i] - '0'); k++ ){
                   dup[y] = ' ';
                   
                   y++;
               }
           }
        else{
            dup[y] = buff[i];
            y++;
        }   
    }

        for(int i=0; dup[i]!='\0'; i++)
    {
        if(dup[i]=='a' || dup[i]=='e' || dup[i]=='i' || dup[i]=='o'
           || dup[i]=='u' || dup[i]=='A' || dup[i]=='E' || dup[i]=='I'
           || dup[i]=='O' || dup[i]=='U')
        {
            vowelCount = i;
        }
    }
        
        
        size_t vowelSize = sizeof(buff)/sizeof(buff[0]);
        char vowelArray[vowelSize +1];
        destination_size = sizeof (vowelArray);

        strncpy(vowelArray, dup, destination_size);
        


        if (vowelCount >= constantCount){
            for(int i=0; constantArray[i]!='\0'; i++){
                if((vowelArray[i] == ' ') && (constantArray[i] != ' ')){
                    vowelArray[i] = constantArray[i];                    
                }
            }
            
            send(fd,vowelArray,SIZE,0);
            memset(constantArray ,0 , SIZE);
            memset(vowelArray ,0 , SIZE);
            

        }
        else if (vowelCount < constantCount){
            for(int i=0; vowelArray[i]!='\0'; i++){
                if((constantArray[i] == ' ') && (vowelArray[i] != ' ')){
                    constantArray[i] = vowelArray[i];
                }
            }
            
            send(fd,constantArray,SIZE,0);
            memset(constantArray ,0 , SIZE);
            memset(vowelArray ,0 , SIZE);
            
        }
        

        
    }
    else{break;}

	
    }
}

void echoSimple(int fd)
{
	char buff[SIZE], blankSpace = ' ',i;

    
    
    while(1){
    memset(buff ,0 , SIZE);
    recv(fd,buff,SIZE,0);
    

    if (strchr(buff, '1') != NULL)
    {
        recv(fd,buff,SIZE,0);
        size_t ArraySize = sizeof(buff)/sizeof(buff[0]);
        char constantArray[ArraySize +1], vowelArray[ArraySize + 1];
        size_t destination_size = sizeof (constantArray);
        

        strncpy(constantArray, buff, destination_size); 
        strncpy(vowelArray, buff, destination_size); 
         

        
        
    for(i=0; buff[i]!='\0'; i++)
    {
        if(buff[i]=='a' || buff[i]=='e' || buff[i]=='i' || buff[i]=='o'
           || buff[i]=='u' || buff[i]=='A' || buff[i]=='E' || buff[i]=='I'
           || buff[i]=='O' || buff[i]=='U')
        {
            constantArray[i] = blankSpace;
        }
    }
    
    for(i=0; buff[i]!='\0'; i++)
    {
        if(buff[i]!='a' && buff[i]!='e' && buff[i]!='i' && buff[i]!='o'
           && buff[i]!='u' && buff[i]!='A' && buff[i]!='E' && buff[i]!='I'
           && buff[i]!='O' && buff[i]!='U')
        {
            
            vowelArray[i] = blankSpace;
        }
    }
    
       

        send(fd,constantArray,SIZE,0);
        

        int sockfd;
    char buffer[SIZE];
    
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(num);

    num++;

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);  //len is value/resuslt    

    n = recvfrom(sockfd, (char *)buffer, SIZE,
                0, ( struct sockaddr *) &cliaddr,
                (socklen_t*)&len);
    buffer[n] = '\0';
    
    sendto(sockfd, vowelArray, SIZE,
        0, (const struct sockaddr *) &cliaddr,
            len);
        
    }
    else if (strchr(buff, '2') != NULL)
    {
        memset(buff ,0 , SIZE);
        int vowelCount = 0, constantCount = 0;

        recv(fd,buff,SIZE,0);
        for(int i=0; buff[i]!='\0'; i++)
    {
        if(buff[i]!='a' && buff[i]!='e' && buff[i]!='i' && buff[i]!='o'
           && buff[i]!='u' && buff[i]!='A' && buff[i]!='E' && buff[i]!='I'
           && buff[i]!='O' && buff[i]!='U' && buff[i] != ' ')
        {
            
            constantCount = i;
        }
    }
        size_t ArraySize = sizeof(buff)/sizeof(buff[0]);
        char constantArray[ArraySize +1];
        size_t destination_size = sizeof (constantArray);
        

        strncpy(constantArray, buff, destination_size); 
        memset(buff ,0 , SIZE);
        int sockfd;
    char buffer[SIZE];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(num);

    num++;

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);  //len is value/resuslt    

    n = recvfrom(sockfd, buff, SIZE,
                0, ( struct sockaddr *) &cliaddr,
                (socklen_t*)&len);
    buff[n] = '\0';

        for(int i=0; buff[i]!='\0'; i++)
    {
        if(buff[i]=='a' || buff[i]=='e' || buff[i]=='i' || buff[i]=='o'
           || buff[i]=='u' || buff[i]=='A' || buff[i]=='E' || buff[i]=='I'
           || buff[i]=='O' || buff[i]=='U')
        {
            vowelCount = i;
        }
    }
              
        size_t vowelSize = sizeof(buff)/sizeof(buff[0]);
        char vowelArray[vowelSize +1];
        destination_size = sizeof (vowelArray);

        strncpy(vowelArray, buff, destination_size);
        if (vowelCount >= constantCount){
            for(int i=0; constantArray[i]!='\0'; i++){
                if((vowelArray[i] == ' ') && (constantArray[i] != ' ')){
                    vowelArray[i] = constantArray[i];                    
                }
            }
            
            send(fd,vowelArray,SIZE,0);
            memset(constantArray ,0 , SIZE);
            memset(vowelArray ,0 , SIZE);
            

        }
        else if (vowelCount < constantCount){
            for(int i=0; vowelArray[i]!='\0'; i++){
                if((constantArray[i] == ' ') && (vowelArray[i] != ' ')){
                    constantArray[i] = vowelArray[i];
                }
            }
            
            send(fd,constantArray,SIZE,0);
            memset(constantArray ,0 , SIZE);
            memset(vowelArray ,0 , SIZE);
            
        }          
    }
    else{break;}

    }
}