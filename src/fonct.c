# include <stdio.h>
# include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 4

typedef enum
{
	none    = 1,
    doubleL = 2,
    tripleL = 3,
    doubleM = 4,
    tripleM = 5
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




void ajouter_score (cell ruzzle[N][N], coord pos, t_score * score)
{
	if (ruzzle[pos.x][pos.y].bonus < 4)
	{
		score->point += ruzzle[pos.x][pos.y].point*ruzzle[pos.x][pos.y].bonus;
	}
	else
	{
		score->multi *= ruzzle[pos.x][pos.y].bonus-2;
	}
}


void init_visit (cell ruzzle[N][N])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			ruzzle[i][j].visited = 0;
		}
	}	
}

/*	init prend en paramètre, la chaine à l'origine du ruzzle, le tableau
**	de type cell ou on va écrire chaque lettres et ces multiplicateurs
**	et ouvre les fichier du dictionnaire et de sortie des solutions.
*/

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

/*	create_new_dico prend la grille du ruzzle et un fichier
**	ouvert en lecture (le dictionnaire) et regarde pour chaque
**	mot si les lettres de celui-ci sont toutes présentes (le
**	mot est-il faisable avec cette grille ?) et suprime les 
**	mots infaisable.
*/


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

/*	find_letter prend en paramètre un caractère, ces coordonnées
**	ainsi que la grille du ruzzle et va chercher si au alentour
**	des coordonnées donné il y a la lettre suiante du mot à
**	vérifié (la lettre c est-elle voisine ?).
*/

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

/*	find_word prend en paramètre la grille du ruzzle et un mot,
**	cherche le mot a l'aide d'autre fonction et l'inscrit dans
**	la liste des solution avec son score.
*/

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
	init_visited(ruzzle);
}
