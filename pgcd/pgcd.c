#include <stdio.h>


int pgcd ( int a , int b)
{
	printf("entré dans pgcd(%d , %d)\n",a ,b);
	int res;
	if (a > b )
	{
		if ( a%b == 0 )
		{ 
			res = b;
		}
		else
		{
			res= pgcd(b,a%b);
		}
	}
	else
	{	
		if (b%a == 0)
			res = a;
		else 
			res = pgcd(a,b%a);
	}
	printf("sortie de pgcd(%d , %d) = %d)\n",a,b,res);
	return res;
}
