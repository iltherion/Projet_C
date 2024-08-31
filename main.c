#include <stdlib.h>
#include <stdio.h>
#include "hello.h"
#include "pgcd/pgcd.h"

int main(int argc , char *argv[]  )
{
	
	erreur_argc(verif_argc(argc,3));	
	
	printf ("Le nombre d'argument : %d \n",atoi(argv[1]));
	printf("Le pgcd de %d et %d est: %d\n",atoi(argv[1]),atoi(argv[2]),pgcd(atoi(argv[1]),atoi(argv[2])));	



	return 0;
}
