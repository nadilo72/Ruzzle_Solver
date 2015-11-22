#include <string.h>
#include <ctype.h>
#include "ruzzle.h"
#include "liste.h"
/********************************************//**
 * \brief
 *
 * \param
 * \param
 * \param
 * \param
 * \return
 *
 ***********************************************/
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
                if(entree[N*N*i+N*j+2]=='M')
                {
                	mult=2;
                }
                else // si entree[N*N*i+N*j+2]=='L ou espace'
                {
                	mult=1;
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


/********************************************//**
 * \brief
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
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
        fscanf(dico,"%s",word);
        if(strpbrk(word,outLetters)==NULL && strlen(word)<=16)
        {
            fprintf(newdico,"%s\n",word);
        }
    }
    fclose(dico);
    fclose(newdico);
    return 0;
}


/********************************************//**
 * \brief
 *
 * \param
 * \param
 * \param
 * \return
 *
 ***********************************************/
bool find_letter(char c, coord * pos, cell ruzzle[N][N])
{
	bool trouve = false;
	for(int j=-1;j<=1 && !trouve;j++)
	{
		for(int i=-1; i<=1 && !trouve;i++)
		{
		    if(i!=0||j!=0)
            {
                if(pos -> x + i >=0 && pos -> x + i <N && pos -> y + j >=0 && pos -> y + j <N )
                {
                    if(c == ruzzle[pos -> x + i][pos -> y + j].character && ruzzle[pos -> x + i][pos -> y + j].visited == 0)
                    {
                        trouve = true;
                        pos -> x += i;
                        pos -> y += j;
                        ruzzle[pos->x][pos->y].visited=1;
                    }
                }
            }
		}
	}
	return trouve;
}


/********************************************//**
 * \brief
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
void ajouter_mot(char * mot, int score)
{
    bool place=false;
    char tmpWord[20];
    int tmpScore;
    if(!liste_vide())
    {
        en_tete();
        while(!hors_liste() && !place)
        {
            valeur_elt(tmpWord,&tmpScore);
            if(tmpScore<score)
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


/********************************************//**
 * \brief
 *
 * \param
 * \param
 * \param
 * \return
 *
 ***********************************************/
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


/********************************************//**
 * \brief
 *
 * \param
 * \return
 *
 ***********************************************/
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


/********************************************//**
 * \brief
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
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
			if(tolower(mot[0])==tolower(ruzzle[i][j].character))
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
		if(find_letter(mot[i],&coordonnee,ruzzle))
		{
			if(strlen(mot)>1)
            {
                ajouter_score(ruzzle, coordonnee, &score);
            }
		}
		else
		{
            possible = false;
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


/********************************************//**
 * \brief
 *
 * \param
 * \return
 *
 ***********************************************/
int print_list(FILE * output)
{
    char mot[20];
    int score;
    en_tete();
    output = fopen("output.txt","w");
    if(output==NULL)
    {
        return 1;
    }
    while(!hors_liste())
    {
        valeur_elt(mot,&score);
        fprintf(output,"%i - %s\n",score,mot);
        suivant();
    }
    fclose(output);
    return 0;
}
