#include <stdio.h>
#include <stdint.h>  //uint
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>

#include <arpa/inet.h>
#include <sys/types.h>         
#include <sys/socket.h> 
#include <netinet/in.h>

#define IPPROTO_VRRP  112 

extern int errno ; 

// Calculate the checksum (RFC 1071)
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

typedef struct _vrrphdr {			/* rfc2338.5.1 */
	uint8_t			vers_type;	/* 0-3=type, 4-7=version */
	uint8_t			vrid;		/* virtual router id */
	uint8_t			priority;	/* router priority */
	uint8_t			naddr;		/* address counter */
	uint8_t			auth_type;	/* authentification type */
	uint8_t 		adver_int;	/* advertisement interval (in sec) */
	uint16_t		chksum;		/* checksum (ip-like one) */
	/* here <naddr> ip addresses */
	/* here authentification infos */
} vrrphdr_t;



int main( int argc , char * argv[]) {

	int errnum;
	int vrrp_sd;
	struct sockaddr_in  * vrrpaddr ;
	vrrphdr_t h_vrrp;
	
	char * ip = argv[1];
	printf("Ip = %s\n",ip);
	
	vrrp_sd = socket(AF_INET , SOCK_RAW , IPPROTO_VRRP );
	if (vrrp_sd < 0 ) {
		printf("Erreur pas de file descriptor\n");
		return 1;
	}
	else {
		printf("File descriptor %d\n" , vrrp_sd);
	}
	
	vrrpaddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in)); 
	vrrpaddr->sin_family = AF_INET;
	vrrpaddr->sin_port = 0; 
	if (inet_pton(AF_INET, "192.168.1.1" , &(vrrpaddr->sin_addr)) == -1) {
		printf("erreur inet_pton\n");
	}

	bzero(&h_vrrp ,sizeof(h_vrrp));
	h_vrrp.vers_type = 33;
	h_vrrp.vrid = 100;
	h_vrrp.priority = 99;
	h_vrrp.adver_int = 1;
	h_vrrp.chksum = checksum(&h_vrrp, sizeof(h_vrrp));  	
	if (sendto(vrrp_sd, &h_vrrp, sizeof(h_vrrp), 0, (struct sockaddr*)vrrpaddr,sizeof(*vrrpaddr))<= 0 ) {
		printf("erreur\n");
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		fprintf(stderr, "Error sendto: %s\n", strerror( errnum ));  
	}

	close(vrrp_sd);	
 	free(vrrpaddr);
	return 0 ; 
}
