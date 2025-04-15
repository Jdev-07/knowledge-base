#include <sys/types.h>
#include <sys/sockets.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **npv)
{
if (argc >0)
	{ int lclient, port, fd1, fd2;
	port=atoi(npv[1]);

	int nbyte;
	char buf[100];

	struct sockaddr_in server, client;

	memset(&server, 0, sizeof(server));
	server.sin_family	= AF_INET;
	server.sin_port		= htons(port);
	server.sin_addr.s_addr	= INADDR_ANY;

	if (( fd1=socket(AF_INET, SOCK_STREAM, 0) )<0)
		{printf("Error when trying to open the port \n");
		return -1;
		}

	if (bind(fd1,(struct sockaddr*)&server, sizeof(server))==-1)
		{printf("Error when trying to assign the IP and port number to the socket \n");
		return -1;
		}

	if (listen (fd1, 3)==-1)
		{printf("Error when trying to set the socket as passive \n");
		return -1;
		}

	lclient = sizeof(client);
	while(1)
		{fd2 = accept(fd1,( struct sockaddr *)&client, &lclient);
		if (fd2 < 0)
			{printf("Error accepting the connection \n");
			return -1;
			}
		send(fd2, "Welcome to the Aby's Server (UBUNTU) \n ", 26, 0);

		if ((nbyte=recv(fd2, buf, 100, 0))==-1)
			{printf("Error receiving the message \n");
			}
		buf[nbyte]='\0';
		printf("Client message: %s \n", buf);
		close(fd2);
		}
	}
else
	{printf("Did not enter to the port number \n");
	}
return 0;
}
