#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "liste.h"

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
    if(strlen(entree)==(N*N*4))
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                sortie[i][j].character = tolower(entree[N*N*i+N*j]);
                sortie[i][j].point = entree[N*N*i+N*j+1] - '0';
                if(entree[N*N*i+N*j+2]=='L' || entree[N*N*i+N*j+2]==' ')
                {
                	mult=1;
                }
                else if(entree[N*N*i+N*j+2]=='M')
                {
                	mult=2;
                }
                if(entree[N*N*i+N*j+3]=='D')
                {
                	sortie[i][j].bonus=mult*2;
                }
                else if(entree[N*N*i+N*j+3]=='T')
                {
                	sortie[i][j].bonus=mult*3;
                }
                else
                {
                    sortie[i][j].bonus=mult*1;
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
    else
    {
        fclose(dico);
    }
    output = fopen("output.txt","w");
    if(output==NULL)
    {
        erreur += 4;
    }
    else
    {
        fclose(output);
    }
    return erreur;
}

int create_new_dico(cell ruzzle[N][N], FILE * dico)
{
    dico = fopen("dictionnaire.txt","r");
    FILE * newdico;
    int k=0;
    bool sortie;
    char word[30];
    char inLetters[N*N+1];
    char outLetters[26];
    char totLetters[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
        sortie=0;
        for(int j=0;j<N*N;j++)
        {
            if(tolower(totLetters[i])==inLetters[j])
            {
                sortie=1;
            }
        }
        if(sortie!=1)
        {
            outLetters[k]=tolower(totLetters[i]);
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
    fclose(newdico);
    return 0;
}

bool find_letter(char c, coord * coordonnee, cell ruzzle[N][N])
{
	bool trouve = false;
	for(int i=-1;i<=1 && !trouve;i++)
	{
		for(int j=-1; j<=1 && !trouve;j++)
		{
		    if(i!=0||j!=0)
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
	return trouve;
}

void ajouter_mot(char * mot, int score)
{
	printf("%i - %s\n",score,mot);
	int elem;
	char tmp[20];
	bool place=false;
	if(!liste_vide())
	{
		en_tete();
		while(!hors_liste() && !place)
		{
			valeur_elt(tmp,&elem);
			if(score < elem)
			{
				ajout_gauche(mot,score);
				place=true;
			}
			suivant();
		}
		if(!place)
		{
			en_queue();
			ajout_droit(mot,score);
		}
	}
	else
	{
		ajout_droit(mot,score);
	}
}

void ajouter_score (cell ruzzle[N][N], coord pos, t_score * score)
{
	if (ruzzle[pos.x][pos.y].bonus < 4)
	{
		score->point += ruzzle[pos.x][pos.y].point*ruzzle[pos.x][pos.y].bonus;
	}
	else
	{
	    score->point += ruzzle[pos.x][pos.y].point;
		score->multi *= ruzzle[pos.x][pos.y].bonus/2;
	}
}

void init_visited (cell ruzzle[N][N])
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

void find_word(cell ruzzle[N][N], char mot[])
{
	t_score score;
	score.point=0;
	score.multi=1;
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
				ajouter_score(ruzzle, coordonnee, &score);
			}
		}
	}
	for(int i=1; i<strlen(mot) && possible; i++)
	{
		possible=find_letter(mot[i],&coordonnee,ruzzle);
		if(possible)
		{
            ajouter_score(ruzzle, coordonnee, &score);
		}
	}
	if(possible)
	{
		if(strlen(mot)>1)
		{
		    ajouter_mot(mot, score.point*score.multi);
		}
	}
	init_visited(ruzzle);
}

void print_list()
{
    char mot[30];
    int score;
    FILE * out=fopen("output.txt","w");
    if(!liste_vide())
    {
        en_queue();
        while(!hors_liste())
        {
            valeur_elt(mot,&score);
            //printf("%i - %s\n",score,mot);
            fprintf(out,"%i - %s\n",score,mot);
            precedent();
        }
    }
    fclose(out);
}

int main(int argc, char * argv[])
{
	//test
	char input[N*N*4];
	printf("%i",argc);
	if(argc==1)
	{
		strcpy(input,"O1  S1DLL1  C4  E1  L1  A1  I1  T1  A1  N1  T1  M3  Y4  S1  E1  ");//  O  S  L  C
	}                                                                                    //  E  L  A  I
                                                                                         //  T  A  N  T
	//fin_test                                                                           //  M  Y  S  E
    cell ruzzle[N][N];
    FILE * dico=NULL;
    FILE * output=NULL;
    init_liste();
    char mot[20];

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
        print_list();
    }
    else
    {
        printf("ERREUR");
    }
    return 0;
}

