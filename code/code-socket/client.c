#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 5984
#define BUFF_SIZE 4096

int main(int argc, const char *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[BUFF_SIZE] = {0};

	/* [C1]
         * An endpoint is created for communication between server and client.                        
         * sock contains the file descriptor that refers to the endpoint                         
         * AF_INET is the communication domain for IPv4 Internet Protocol                             
         * SOCK_STREAM(TCP) provides a reliable, two-way, connection-based byte                       
         * stream.                                                                                    
         * The last parameter is Internet Protocol which is 0.                                        
         * socket() function returns a file descriptor for the new socket on                          
         * success. On failure -1 is returned.                                                        
         */ 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	/* [C2]
	 * sockaddr_in is used to specify a transport address and port.
	 * memset is used to set the bytes represented by serv_addr to 0.
         * sin_faimly is set as AF_INET as address family for IPv4
         * htons i.e. host-to-network-short swaps the endianness of a short. 
	 */
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	/* [C3]
	 * inet_pton converts the IPv4 string address "127.0.0.1" into a netwrk
	 * address structure in the AF_INET address family and stores in 
	 * sin_addr which is destination(server) address.
	 * Returns 1 on success, -1 on invalid address and errno=EAFNOSUPPORT. 
	 */
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	/* [C4]
	 * connect initiates a connection from file descriptor sock to serv_addr.
	 * Return value is 0 on success, -1 on failure and errno is set.
	 */
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}


	/* [C5]
	 * After connection is successful, client waits for user input before 
	 * sending message.
	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [C6]
	 * send() is used to send a hello message from client to server. 
	 * send() can be used only when socket is in connected state.
	 * sock is the socket where connection is established.
	 * hello msg is sent in buffer with buffer length.
	 * flag is set to 0 here.
	 */
	send(sock , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");

	/* [C7]
	 * read the msg recieved from server in the file descriptor sock.
	 * read() will load upto 1024 bytes in buffer.
	 */
	if (read( sock , buffer, 1024) < 0) {
		printf("\nRead Failed \n");
		return -1;
    }
	printf("Message from a server: %s\n",buffer );
	return 0;
}
