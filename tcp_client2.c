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

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[32]; //buffer
	int read_len;
	int cnt_i;
	
	if(argc !=3)
	{
		fprintf(stderr, "%s <IP> <PORT>\n", argv[0]);
		exit(1);
	}
	
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		error_handling("socket() error");
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); //"127.0.0.1" => 32-bit value
	serv_addr.sin_port = htons(atoi(argv[2])); //'9190" => 9190
	
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("connect() error");
	}
	
	printf("excuting connect() function\n");
	
	for(cnt_i = 0; cnt_i < 3; cnt_i++) // wait for 3 sec
	{
		sleep(1); 
		printf("Wait time %d\n", cnt_i); 
	}
	
	read_len = read(sock, message, sizeof(message)); // read_len = 13
	
	
	printf("Message from server: %s\n", message);
	printf("Function read call count: %d\n", read_len);
	
	close(sock);
	return 0;
}
