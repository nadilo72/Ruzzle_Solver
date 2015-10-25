#include <stdio.h>
#include <stdlib.h>

#define N 4

int init(char entree[], char sortie[N][N][3], FILE * dico, FILE * output)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            sortie[i][j][0] = entree[16*i+4*j];
            sortie[i][j][1] = entree[16*i+4*j+1];
            sortie[i][j][2] = entree[16*i+4*j+2]+entree[16*i+4*j+3];
        }
    }
    dico = fopen("dictionnaire.txt","r");
    output = fopen("output.txt","w");
    return 0; //TODO verif si tout se passe bien sinon return 1;
}

int find_word(int i, int j, char ruzzle[N][N][3])
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
            find_word(i,j,ruzzle);
        }
    }
    return 0;
}
