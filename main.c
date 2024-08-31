#include <stdlib.h>
#include <stdio.h>
#include "hello.h"
#include "pgcd/pgcd.h"

int main(int argc , char *argv[]  )
{
	
		
	erreur_argc(verif_argc(argc,3));	
		
	if (atoi(argv[1])== 0 || atoi(argv[2])==0)
		goto fin ;
	printf ("Le nombre d'argument : %d \n",atoi(argv[1]));
	printf("Le pgcd de %d et %d est: %d\n",atoi(argv[1]),atoi(argv[2]),pgcd(atoi(argv[1]),atoi(argv[2])));	


	fin :
		fprintf( stderr, "Vous avez mis un 0 ou un mot en argument\n");
		return 3;
	
	return 0;
}
