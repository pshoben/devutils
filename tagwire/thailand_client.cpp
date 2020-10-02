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
#include "emapi.h"
#include <sstream>

#include "EmapiTagwireWrapper.h"


using namespace emapi;
using std::string;
using std::stringstream;
using std::cout;

EmapiTagwireWrapper tpl_req;


#define DEFAULT_PORT    6565 // 8080
#define DEFAULT_HOST    "127.0.0.1"

//#define MAX_CONN        16
//#define MAX_EVENTS      32
//#define BUF_SIZE        16
#define MAX_LINE        512

bool g_interactive = true;

unsigned short g_port= DEFAULT_PORT;
char g_host[HOST_NAME_MAX]=DEFAULT_HOST;
char g_send_string[MAX_LINE-1]="test send";
int g_send_repeats = -1 ; // default -1 = send forever
struct timespec g_send_wait;

void print_twstring(char * s) 
{
	try {
	string tpl_str{s};
	TagwireDecoder decoder{ (const unsigned char *)tpl_str.c_str(),
				0,(unsigned int) tpl_str.size()};  

	cout << "got tagwire string : \"" << tpl_str << "\"\n";
	tpl_req.unpack(decoder);
	cout << "unpacked:\n" << tpl_req.to_string("");
	} catch ( std::exception e )
	{
		printf("Tagwire Decode failed\n");
	}
}


void test_tpl() 
{
	stringstream ss;
	ss  << EmapiMessageType_EmapiTaxPreLogonReq << "=[" 
		<< "1=T"
		<< "|2=member"
		<< "|3=user"
		<< "|4=1"
		<< "|5=2"
		<< "|6=3"
		<< "]";
	string tpl_str{ss.str()};
	TagwireDecoder decoder{ (const unsigned char *)tpl_str.c_str(),
				0,(unsigned int) tpl_str.size()};  

	cout << "test string : \"" << tpl_str << "\"\n";
	tpl_req.unpack(decoder);
	cout << "wrapper\n" << tpl_req.to_string("");

	TagwireEncoder encoder(tpl_req.getMessageType());
	tpl_req.pack(encoder);

	cout << "packed: " << encoder.getBuffer() << "\n";

}

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

void print_menu_options() 
{
	printf("options:\n*1 send taxprelogonreq\n");
	printf("options:\n*2 send taxconnnectorentry\n");
	printf("options:\n*3 send taxprelogonrsp\n");
	printf("options:\n*4 send abstractmeevent\n");
	printf("options:\n*5 send proteusrefdatamessage\n");
	printf("options:\n*6 send requestmessage\n");
	printf("options:\n*7 send simpleresponse\n");
	printf("options:\n*8 send responsemessage\n");
	printf("options:\n*9 send msg_publicmulticastaddress\n");
	printf("options:\n*a send msg_publicmulticastpartition\n");
	printf("options:\n*b send msg_publicmulticastcontent\n");
	printf("options:\n*c send msg_taxlogonreq\n");
	printf("options:\n*d send msg_taxlogonrsp\n");
}

void client_run()
{
	int n;
	int c;
	int sockfd;
	char buf[MAX_LINE];
	struct sockaddr_in srv_addr;

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

		char msg_abstractmeevent[]="238=[1=1|2=2|3=timeofevent|4=T]";
		char msg_proteusrefdatamessage[]="236=[1=key|2=cacheid|3=3|4=4|5=uniqueobjectid|6=timestamp|7=F]";
		char msg_taxprelogonreq[]="66=[1=T|2=member|3=user|4=1|5=2|6=3]";
		
		string msg_taxconnectorentry= "68=[1=1|2=ipaddress|3=3|4=[4|4]|5=[5|5]]";
		string tce = msg_taxconnectorentry;

		string msg_taxprelogonrsp="64=[1=1|2=message|3=[3|3]|4=requestid|5=reply|6=address|7=7|8=8|"
					  "9=[" + tce + "|" + tce + "]|10=messagref]";
		char msg_requestmessage[]="237=[1=T]";
		char msg_simpleresp[]="231=[1=1|2=message|3=[3|3]|4=requestid|5=reply|6=messagereference]";
		char msg_responsemessage[]="230=[1=1|2=message|3=[3|3]|4=requestid|5=messagereference]";

		string msg_publicmulticastaddress = "110=[1=key|2=cacheid|3=3|4=4|5=uniqueobjectid|6=timestamp|7=pmcaddress|8=8"
						"9=pmcsourceaddress|10=pmcpartitionid|11=F";
		string pma = msg_publicmulticastaddress;

		string msg_publicmulticastpartition = "109=[1=key|2=cacheid|3=3|4=4|5=uniqueobjectid|6=timestamp|7=pmcpartitionid|8=payloadcontenttype"
						"|10=10|11=11|12=12|13=pmccontentid|14=[" + pma + "]|[" + pma + "]|15=F";
		string pmp = msg_publicmulticastpartition;

		string msg_publicmulticastcontent = "108=[1=key|2=cacheid|3=3|4=4|5=uniqueobjectid|6=timestamp|7=pmccontentid|8=flowidlist"
						"|9=subscriptiongrouplist|10=[" + pmp + "]|[" + pmp + "]|11=F]";
		string pmc = msg_publicmulticastcontent;

		string msg_taxlogonreq="63=[1=T|2=member|3=user|4=password|5=5|6=6|7=7|8=8|9=9]";
		string msg_taxlogonrsp="64=[1=1|2=message|3=[3|3]|4=requestid|5=reply|6=T|7=7|8=T|"
					  "9=systemname|10=10|11=11|12=12|13=[" + pmc + "]|[" + pmc + "]|14=messagref]";
	
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
					print_menu_options();
					continue;
				} else if ( buf[1]=='1' ) {
					strcpy( send_buffer, msg_taxprelogonreq );
					//c = strlen( send_buffer );
				} else if ( buf[1]=='2' ) {
					strcpy( send_buffer, msg_taxconnectorentry.c_str());
					//c = strlen( send_buffer );
				} else if ( buf[1]=='3' ) {
					strcpy( send_buffer, msg_taxprelogonrsp.c_str());
				} else if ( buf[1]=='4' ) {
					strcpy( send_buffer,msg_abstractmeevent );
				} else if ( buf[1]=='5' ) {
					strcpy( send_buffer, msg_proteusrefdatamessage );
				} else if ( buf[1]=='6' ) {
					strcpy( send_buffer, msg_requestmessage );
				} else if ( buf[1]=='7' ) {
					strcpy( send_buffer, msg_simpleresp );
				} else if ( buf[1]=='8' ) {
					strcpy( send_buffer, msg_responsemessage );
				} else if ( buf[1]=='9' ) {
					strcpy( send_buffer, msg_publicmulticastaddress.c_str());
				} else if ( buf[1]=='a' ) {
					strcpy( send_buffer, msg_publicmulticastpartition.c_str());
				} else if ( buf[1]=='b' ) {
					strcpy( send_buffer, msg_publicmulticastcontent.c_str());
				} else if ( buf[1]=='c' ) {
					strcpy( send_buffer, msg_taxlogonreq.c_str());
				} else if ( buf[1]=='d' ) {
					strcpy( send_buffer, msg_taxlogonrsp.c_str());
				} else {
					printf("unrecognised option\n");
					print_menu_options();
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
			print_twstring( copy_recv_buffer ); 

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
	test_tpl();

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


