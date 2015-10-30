#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int init(char entree[], char sortie[N][N][3], FILE * dico, FILE * output)
{
    int erreur = 0;
    if(strlen(entree)==(N*N*N))
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                sortie[i][j][0] = entree[N*N*i+N*j];
                sortie[i][j][1] = entree[N*N*i+N*j+1];
                sortie[i][j][2] = entree[N*N*i+N*j+2]+entree[N*N*i+N*j+3];
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

int create_new_dico(char ruzzle[N][N][3], FILE * dico)
{
    FILE * newdico;
    char word[30];
    char letters[N+1];
    newdico = fopen("newdico.txt","w");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            letters[N*i+j] = ruzzle[i][j][0];
        }
        letters[N*N]='\0';
    }
    while(!feof(dico))
    {
        fscanf(dico,"%s",&word);
        if(strpbrk(word,letters)!=NULL)
        {
            fprintf(newdico,"%s\n",word);
        }
    }
    fclose(dico);
    dico = newdico;
    return 0;
}
int find_word(int i, int j, char ruzzle[N][N][3], FILE * dico)
{

    return 0;
}

int main(int argc, char * argv[])
{
    char ruzzle[N][N][3];
    FILE * dico=NULL;
    FILE * output=NULL;
    init(*argv, ruzzle, dico, output);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            find_word(i,j,ruzzle,dico);
        }
    }
    return 0;
}
