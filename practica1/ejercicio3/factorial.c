#include <stdio.h>
#include <stdlib.h>
void main(int argc, char **argv){

	int i,n,valor=1;
	
	if (argc != 2){
	  /* check for valid number of command-line arguments */
	  printf("Usage: %s Numero de processes\n", argv[0]);
	  exit(EXIT_FAILURE);
	}
	n=atoi(argv[1]);
	for(i=2;i<=n;i++){
		valor*=i;
	}
	printf("\n%d! = %d\n",n,valor);
}
