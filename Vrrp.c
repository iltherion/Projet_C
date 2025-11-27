#include <getopt.h>
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
	double			bourrage; 	/* Bit de bourrage */
} vrrphdr_t;

void help(char *nom_programme){
	printf("Utilisation: \n\
	%s --ip <ip_dst>\n\
\n\
\n\
---------------------------------------------------------\n\
Option : \n\
	--ip  ou -i  			==> ip destination du paquet\n\
	--vrid	 	defaut 100	==> groupe vrrp entre 0 et 255\n\
	--prio 		defaut 50	==> Priorité vrrp entre 1 et 255\n\
	--count	 	defaut 1	==> Nombre de paquet envoyé\n\
	--time    	defaut 1	==> Temps entre chaque envoye de paquet\n\
	--verbose ou -v			==> Affiche des infos \n\
	--help ou -h			==> L'aide de la commande\n\
\n\
---------------------------------------------------------\n"
,nom_programme);
}

void option ( int argc , char * argv[] , char ip[] , char * vrid , char * priority , int * nb_p , int * time , int * verbose) {
	
	int opt	;
	int option_index = 0 ;
	static struct option long_options[] = {
		{"ip", required_argument, 0 , 'i'},
		{"vrid" , required_argument, 0 , 'r'},
		{"prio" , required_argument, 0 , 'p'},
		{"count" , required_argument, 0 , 'c'},
		{"time" , required_argument, 0 , 't'},
		{"verbose" , no_argument, 0 , 'v'},
		{"help" , no_argument, 0 , 'h'} 
	};	
	
	while ( (opt = getopt_long(argc, argv, "i:hv", long_options, &option_index)) != -1) {
                if (opt == 'i') {
			strcpy(ip , optarg);
		}
		if (opt == 'r'){
			*vrid = atoi(optarg);
		}
		if (opt == 'p'){
			*priority = atoi(optarg);
		}
		if (opt == 'c'){
			*nb_p = atoi(optarg);
		}
		if (opt == 't'){
			*time = atoi(optarg);
		}
		if (opt == 'v'){
			*verbose = 1;
		}
		if (opt == 'h'){
			help(argv[0]);
			exit(0);
		}		 		
	}
}
	

int main( int argc , char * argv[]) {

	int errnum ;
	int verbose = 0;
	int time = 1; 
	int vrrp_sd;
	int i = 0;
	int nb_p = 1;
	int vrid_int ; 
	char vrid = 100; 
	char priority = 50;
	struct sockaddr_in  * vrrpaddr ;
	vrrphdr_t h_vrrp;
	char ip[32] ;
	
	bzero(ip,sizeof(ip));	
	option( argc , argv , ip , &vrid , &priority , &nb_p , &time , & verbose);
	if (ip[0] == '\0' ) {
		help(argv[0]);
		return 1;
	}	
	
	vrrp_sd = socket(AF_INET , SOCK_RAW , IPPROTO_VRRP );
	if (vrrp_sd < 0 ) {
		printf("Erreur pas de file descriptor\n");
		return 1;
	}
	else {
		if (verbose == 1 ) { 
			printf("File descriptor %d\n" , vrrp_sd);
		}
	}
	
	vrrpaddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in)); 
	vrrpaddr->sin_family = AF_INET;
	vrrpaddr->sin_port = 0; 
	if (inet_pton(AF_INET, ip , &(vrrpaddr->sin_addr)) == -1) {
		printf("erreur inet_pton\n");
	}

	bzero(&h_vrrp ,sizeof(h_vrrp));
	h_vrrp.vers_type = 33;
	h_vrrp.vrid = vrid;
	h_vrrp.priority = priority;
	h_vrrp.adver_int = time;
	h_vrrp.chksum = checksum(&h_vrrp, sizeof(h_vrrp));
	while ( i < nb_p ){  	
		if (sendto(vrrp_sd, &h_vrrp, sizeof(h_vrrp), 0, (struct sockaddr*)vrrpaddr,sizeof(*vrrpaddr))<= 0 ) {
			printf("erreur\n");
			errnum = errno;
			fprintf(stderr, "Value of errno: %d\n", errno);
			fprintf(stderr, "Error sendto: %s\n", strerror( errnum ));  
		}
		if (verbose == 1) {
			printf("Paquet advert vrrp %d envoyé \n",i+1);
		}
		sleep(time);
		i++;
	}

	close(vrrp_sd);	
 	free(vrrpaddr);
	return 0 ; 
}
