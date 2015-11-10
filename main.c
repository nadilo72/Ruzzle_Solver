#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 4

typedef enum
{
	none    = 1,
    doubleL = 2,
    tripleL = 3,
    doubleM = 4,
    tripleM = 6
}bonusEnum;

typedef struct 
{
	unsigned char character;
	unsigned int point;
	bonusEnum bonus;
	unsigned int visited;
} cell;

typedef struct
{
	int x;
	int y;
}coord;

typedef struct
{
	int point;
	int multi;
}t_score;

int init(char entree[], cell sortie[N][N], FILE * dico, FILE * output)
{
    int erreur = 0;
    int mult;
    if(strlen(entree)==(N*N*N))
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                sortie[i][j].character = entree[N*N*i+N*j];
                sortie[i][j].point = entree[N*N*i+N*j+1] - '0';
                if(entree[N*N*i+N*j+2]=='L')
                {
                	mult=1;
                }
                else
                {
                	mult=2;
                }
                if(entree[N*N*i+N*j+3]=='D')
                {
                	sortie[i][j].bonus=mult*2;
                }
                else
                {
                	sortie[i][j].bonus=mult*3;
                }
                sortie[i][j].visited = 0;
            }
        }
    }
    else
    {
        erreur += 1;
    }
    dico = fopen("dictionnaire.txt","r");
    if(dico==NULL)
    {
        erreur += 2;
    }
    output = fopen("output.txt","w");
    if(output==NULL)
    {
        erreur += 4;
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

void find_letter(char c, coord * coordonnee, cell ruzzle[N][N])
{
	bool trouve = false;
	for(int i=-1;i<=1 && !trouve;i++)
	{
		for(int j=-1; j<=1 && !trouve;j++)
		{
			if(coordonnee -> x + i >=0 && coordonnee -> x + i <N && coordonnee -> y + j >=0 && coordonnee -> y + j <N )
			{
				if(c == ruzzle[coordonnee -> x + i][coordonnee -> y + j].character && ruzzle[coordonnee -> x + i][coordonnee -> y + j].visited == 0)
				{
					trouve = true;
					coordonnee -> x += i;
					coordonnee -> y += j;
					ruzzle[coordonnee->x][coordonnee->y].visited=1;
					
				}
			}
		}
	}
}

//ajouter_score(cell ruzzle[N][N], coord coordonnee, t_score * score) - incrémente le score de la valeur de la case envoyé en paramètre
//ajouter_mot(char mot[]) - ajoute le mot dans la liste, suivit du score associé. La liste est trié en ordre décroissant!!
//reInitVisited(cell ruzzle[N][N]) - réinitialise la valeur de visited de toutes les cases du ruzzle

void find_word(cell ruzzle[N][N], char mot[])
{
	t_score score;
	bool possible = true;
	bool trouve = false;
	coord coordonnee;
	
	for(int i = 0; i<N && !trouve; i++)
	{
		for(int j=0; j<N && !trouve; j++)
		{
			if(mot[0]==ruzzle[i][j].character)
			{
				coordonnee.x=i;
				coordonnee.y=j;
				trouve=true;
				ruzzle[coordonnee.x][coordonnee.y].visited=1;
			}
		}
	}
	for(int i=1; i<strlen(mot) && possible; i++)
	{
		find_letter(mot[i],&coordonnee,ruzzle);
		if(coordonnee.x==-1)
		{
			possible = false;
		}
		else
		{
			ajouter_score(ruzzle, coordonnee, &score);
		}
	}
	if(possible)
	{
		ajouter_mot(mot, score);
	}
	reInitVisited(ruzzle);
}

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

