#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5984
#define BUFF_SIZE 4096

int main(int argc, const char *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFF_SIZE] = {0};
	char *hello = "Hello from server";

	/* [S1]
	 * An endpoint is created for communication between server and client.
	 * server_fd contains the file descriptor that refers to the endpoint
	 * AF_INET is the communication domain for IPv4 Internet Protocol
	 * SOCK_STREAM(TCP) provides a reliable, two-way, connection-based byte 
	 * stream.
	 * The last parameter is Internet Protocol which is 0.
	 * socket() function returns a file descriptor for the new socket on 
	 * success. On failure -1 is returned.
	 */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	/* [S2]
	 * Options for file descriptor server_fd are manipulated here.
	 * SQL_SOCKET is used to manipulate options at the socket's API level.
	 * SO_REUSEADDR and SO_REUSEPORT specify the optname.
	 * opt and length of opt are used to access option values for given 
	 * option name
	 * On success 0 is returned. On failure -1 is returned and errno is set
	 */
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		       &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	/* [S3]
	 * sockaddr_in is used to specify a transport address and port.
	 * sin_faimly is set as AF_INET as address family for IPv4
	 * sin_addr.s_addr of in_addr structure contains IPv4 trabsport address
	 * htons i.e. host-to-network-short swaps the endianness of a short.
	 */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	/* [S4]
	 * bind funtion binds the address and port specified in sockaddr_in
	 * above to the socket descriptor server_fd.
	 * On success 0 is returned. On failure -1 is returned and errno is set
	 */
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	/* [S5]
	 * server_fd starts listening for a client message.
	 * 3 specifies the backlog to which the queue of pending connections
	 * grows.
	 * On success 0 is returned. On failure -1 in returned and errno is set
	 */
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* [S6]
	 * accept extracts the first connection on the queue for listening
	 * it forms a new socket connection between client extracted and 
	 * server_fd.
	 * Return value is the file descriptor for new socket created.
	 */
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
				 (socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	/* [S7]
	 * server waits for an input from user before printing the message 
	 * from client.
	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [S8]
	 * The message from client contained in the new_socket descriptor
	 * is put into the buffer with read command and buffer is printed.
	 */
	if (read( new_socket , buffer, 1024) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("Message from a client: %s\n",buffer );

	/* [S9]
	 * After recieving a message from client, server sends a hello message 
	 * to client.
	 */
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0;
}
