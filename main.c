#include <stdlib.h>
#include <stdio.h>
#include "hello.h"
#include "pgcd/pgcd.h"

int main(int argc , char *argv[]  )
{
	int erreur;
	erreur = hello();
	
	erreur_argc(verif_argc(argc,3));	
	
	printf ("Le nombre d'argument : %d \n",atoi(argv[1]));
	printf("Le pgcd de %d et %d est: %d\n",atoi(argv[1]),atoi(argv[2]),pgcd(atoi(argv[1]),atoi(argv[2])));	


	if (erreur != 0)
		printf("Erreur dans hello\n");

	return 0;
}
