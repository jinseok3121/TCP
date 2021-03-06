#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	int serv_sock; // listen socket
	int clnt_sock; // data socket
	
	struct sockaddr_in serv_addr;	// server's IP and Port
	struct sockaddr_in clnt_addr; // client's IP and Port
	socklen_t clnt_addr_size;	//size of struct
	int cnt_i;
	
	char message[] = "Hello World!";
	
	if(argc !=2) //error message
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // IPv4, TCP
	if(serv_sock == -1)  // If can't generate socket
	{
		error_handling("socket() error");
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr)); 
	serv_addr.sin_family=AF_INET; // what address type IPv4
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("bind() error");
	}
	
	if(listen(serv_sock, 5) == -1)
	{
		error_handling("listen() error");
	}
	
	// wait status for connection request fron clients
	clnt_addr_size=sizeof(clnt_addr);
	printf("before accept\n");
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	printf("after accept\n");
	
	if(clnt_sock == -1)
	{
		error_handling("accept() error");
	}
	
	for(cnt_i = 0; cnt_i < sizeof(message); cnt_i++)
	{
		write(clnt_sock, &message[cnt_i], 1);
		
	}
	
	close(clnt_sock);
	close(serv_sock);
	
	return 0;

}

//EOF
