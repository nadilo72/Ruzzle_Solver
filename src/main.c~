#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 4


int main(int argc, char * argv[])
{
    cell ruzzle[N][N];
    FILE * dico=NULL;
    FILE * output=NULL;
    char mot[20];
	
    init(*argv, ruzzle, dico, output);
    create_new_dico(ruzzle,dico);
	while(!feof(dico))
	{
		fscanf(dico,"%s",mot);
		find_word(ruzzle,mot);
	}
    return 0;
}

