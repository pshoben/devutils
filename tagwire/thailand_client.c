/*
 * ref: https://github.com/onestraw/epoll-example 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>

#define DEFAULT_PORT    8080
#define DEFAULT_HOST    "127.0.0.1"

//#define MAX_CONN        16
//#define MAX_EVENTS      32
//#define BUF_SIZE        16
#define MAX_LINE        256

bool g_interactive = false;

unsigned short g_port= DEFAULT_PORT;
char g_host[HOST_NAME_MAX]=DEFAULT_HOST;
char g_send_string[MAX_LINE-1]="test send";
int g_send_repeats = -1 ; // default -1 = send forever
struct timespec g_send_wait;


/** Returns true on success, or false if there was an error */
bool set_socket_blocking(int fd, bool blocking)
{
   if (fd < 0) return false;

#ifdef _WIN32
   unsigned long mode = blocking ? 0 : 1;
   return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags == -1) return false;
   flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif
}
	
static void set_sockaddr(struct sockaddr_in *addr)
{
	bzero((char *)addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(g_port);
}

void client_run()
{
	int n;
	int c;
	int sockfd;
	char buf[MAX_LINE];
	struct sockaddr_in srv_addr;

	char msg_pretaxlogon[]="66=[1=T|2=member|3=user|4=1|5=2|6=3]";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	set_sockaddr(&srv_addr);

	bool success = set_socket_blocking( sockfd, false );
	printf("set socket non-blocking returned %d\n",success );

	success = connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
 	//while( errno == EINPROGRESS ){
		printf("waiting to connect...\n");
		usleep(1000000);
	//}
	//		perror("connect()");
	//		exit(1);
	//}
	printf("connected\n");

	if( g_interactive ) {
		printf("Interactive mode.\n"
			"Enter q[+newline] to quit\n");

		char copy_recv_buffer[MAX_LINE+1];
		char send_buffer[MAX_LINE+1];
		for (;;) {
			memset( send_buffer, 0 , MAX_LINE+1 );
			memset( copy_recv_buffer, 0 , MAX_LINE+1 );
			char * p = copy_recv_buffer;
			printf("> ");
			fgets(buf, sizeof(buf), stdin);
			if( buf[0]=='q') {
				break;
			} else if (buf[0]=='*') {

				if( buf[1]=='?' ) {
					printf("options:\n*1 send pretaxlogon\n");
					continue;
				} else if ( buf[1]=='1' ) {
					strcpy( send_buffer, msg_pretaxlogon );
					//c = strlen( send_buffer );
				} else {
					printf("unrecognised option\n");
					printf("options:\n*1 send pretaxlogon\n");
					continue;
				}
			} else {
				strcpy( send_buffer, buf ) ;
				c = strlen( send_buffer ) - 1;
				send_buffer[c] = '\0';
			}

			printf("sending message: \"%s\"\n", send_buffer );
			write(sockfd, send_buffer, strlen(send_buffer) + 1);

			int countdown = 1000;
			bzero(buf, sizeof(buf));
			do {	
			       	n = read(sockfd, buf, sizeof(buf));
				if(n>1) {	
					printf("recv %d bytes: %s\n", n, buf);

					memcpy( p, buf, n);
					p+= n;
					bzero(buf, sizeof(buf));
				}
				usleep(1000);
				//c -= n;
				//if (c <= 0) {
			//		break;
				//}
			} while( errno == EWOULDBLOCK && ( n<1 ) && countdown-->0 );
			*p=0; // add null terminator
			printf("recv message:\"%s\"\n",copy_recv_buffer);
		}
	} else {
		int sent_count = 0 ;
		while( g_send_repeats == -1 || sent_count < g_send_repeats ) {
			strncpy(buf, g_send_string, sizeof(buf)-1);
			c = strlen(buf) - 1;
			write(sockfd, buf, c + 1);
			while (errno != EAGAIN && (n = read(sockfd, buf, sizeof(buf))) > 0) {
				bzero(buf, sizeof(buf));
				c -= n;
				if (c <= 0) {
					break;
				}
			}
			if( n<0 && errno != EAGAIN ) {
				// lost connection
				perror("write");
				exit(1);
			}
			nanosleep( &g_send_wait, 0 );
			sent_count++;
		}
	}
	close(sockfd);
}


int main(int argc, char *argv[])
{
	g_send_wait.tv_sec=0;
	g_send_wait.tv_nsec=999999999;
	
	int opt;
	while ((opt = getopt(argc, argv, "ih:p:s:r:w:")) != -1) {
		switch (opt) {
		case 'i':
			g_interactive = true;
			break;
		case 'h':
			strcpy(g_host,optarg);
			break;
		case 'p':
			g_port = atoi(optarg);
			break;
		case 's':
			memset(g_send_string, 0, sizeof(g_send_string));
			strncpy(g_send_string,optarg,sizeof(g_send_string)-1);
			break;
		case 'r':
			g_send_repeats = atoi(optarg);
			break;
		case 'w':
			g_send_wait.tv_nsec = atol(optarg);
			if( g_send_wait.tv_nsec > 999999999 ) 
				g_send_wait.tv_nsec = 999999999;
			break;
		default:
			printf("usage: %s [-s send-string] [-w wait time (nanos)]\n"
		 		"[-r repeats (number of repeats)] [-i (interactive)]\n"
				"[h HOST] -p PORT\n", argv[0]);
			exit(1);
		}
	}
	printf("client using host %s port %hu %s\n",g_host,g_port, g_interactive?"(interactive mode)":"(batch mode)");
	client_run();
	return 0;
}


