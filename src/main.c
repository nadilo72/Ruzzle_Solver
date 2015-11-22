#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "liste.h"
#include "ruzzle.h"

#define N 4

int main(int argc, char * argv[])
{
	char input[N*N*4];
    cell ruzzle[N][N];
    FILE * dico=NULL;
    FILE * output=NULL;
    char mot[20];
    init_liste();

    if(argc==1)
	{
		printf("Entrée la chaine de caractère qui formera la grille.\nCette chaine de caractère doit être formée de 16 partie qui determinnent chacune des lettres de la grille.\nChaque parties doit être de la forme 'L1BB' ou L est une lettre, 1 est le nombre de point de la lettre et BB le bonus eventuelles.\nLes bonus sont : \n  -LD pour lettre compte double\n  -LT pour lettre compte triple\n  -MD pour mot compte double\n  -MT pour mot compte triple\n  -Si aucun bonus, mettre deux espaces\n");
		scanf("%s",input);
	}
	else if(argc == 2)
    {
        strcpy(input,argv[1]);
    }
    if(!init(input, ruzzle, dico, output))
    {
        create_new_dico(ruzzle,dico);
        dico = fopen("newdico.txt","r");
        while(!feof(dico))
        {
            fscanf(dico,"%s",mot);
            find_word(ruzzle,mot);
        }
        fclose(dico);
        print_list(output);
    }
    else
    {
        printf("ERREUR : Verifier la chaine de caractère ou le fichier dictionnaire.txt");
    }
    return 0;
}
