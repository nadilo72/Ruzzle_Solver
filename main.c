#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 4

typedef enum
{
	none    = 0,
    doubleL = 1,
    tripleL = 2,
    doubleM = 3,
    tripleM = 4
}bonusEnum;

typedef struct 
{
	unsigned char character;
	unsigned int point;
	bonusEnum bonus;
	unsigned int visited;
} cell;

int init(char entree[], cell sortie[N][N], FILE * dico, FILE * output)
{
    int erreur = 0;
    if(strlen(entree)==(N*N*N))
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                sortie[i][j].character = entree[N*N*i+N*j];
                sortie[i][j].point = atoi(entree[N*N*i+N*j+1]);
                sortie[i][j].bonus = atoi(entree[N*N*i+N*j+2]+entree[N*N*i+N*j+3]);
                sortie[i][j].visited = 0;
            }
        }
    }
    else
    {
        erreur = 1;
    }
    dico = fopen("dictionnaire.txt","r");
    if(dico==NULL)
    {
        erreur = 2;
    }
    output = fopen("output.txt","w");
    if(output==NULL)
    {
        erreur = 3;
    }
    return erreur;
}

int create_new_dico(cell ruzzle[N][N], FILE * dico)
{
    FILE * newdico;
    int k=0;
    bool sortie;
    char word[30];
    char inLetters[N*N+1];
    char outLetters[26];
    char totLetters[26]="abcdefghijklmnopqrstuvwxyz";
    newdico = fopen("newdico.txt","w");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            inLetters[N*i+j] = ruzzle[i][j].character;
        }
        inLetters[N*N]='\0';
    }
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<N*N;j++)
        {
            if(totLetters[i]==inLetters[j])
            {
                sortie=1;
            }
        }
        if(sortie!=1)
        {
            outLetters[k]=totLetters[i];
            k++;
        }
    }
    outLetters[k]='\0';
    while(!feof(dico))
    {
        fscanf(dico,"%s",&word);
        if(strpbrk(word,outLetters)==NULL && strlen(word)<=16)
        {
            fprintf(newdico,"%s\n",word);
        }
    }
    fclose(dico);
    dico = newdico;
    return 0;
}

int find_word(int i, int j, cell ruzzle[N][N], FILE * dico)
{
	while(!feof(dico)
	{
		
	}
    return 0;
}

int main(int argc, char * argv[])
{
    cell ruzzle[N][N];
    FILE * dico=NULL;
    FILE * output=NULL;
    init(*argv, ruzzle, dico, output);
    create_new_dico()
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            find_word(i,j,ruzzle,dico);
        }
    }
    return 0;
}
