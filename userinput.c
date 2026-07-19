#include <stdio.h>
#include <stdlib.h>

int get_gens(int argc, char *argv[])
{
    if(argc != 3){
	printf("ERROR: Use ./game <generations> <seed>\n");
	return -1;
    }

    char *badchar;
    int gens = strtol(argv[1], &badchar, 10);

    if(*badchar != '\0'){
	printf("ERROR: '%c' is not a valid input\n", *badchar);
	return -1;
	}

    return gens;
}

char *get_seed(int argc, char *argv[])
{
    if(argc != 3){
	printf("ERROR: Use ./game <generations> <seed>");
	return NULL;
    }
    
    return argv[2];
}
