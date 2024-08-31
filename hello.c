#include <stdio.h>
#include <stdlib.h>

void suite()
{
	printf("Bienvenu dans le monde du c\n");
}

int hello()
{
	/*premier commentaire*/
	if (1==1)
	{
		return 1;
	}
	fprintf(stderr ,"Hello_World !!!\n");
	suite();
	return 0;
}

int verif_argc ( int argc , int compare)
{
	if (argc >= compare ) 
		return 0;
	else 
		return 1;
}

void erreur_argc(int retour) 
{
	if (retour)
	{
		printf("Erreur pas assez d'argument\n");
		exit(2);
	}
}
