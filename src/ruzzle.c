﻿
/********************************************//**
 * \file ruzzle.c
 * \brief Fonctions du ruzzle solver
 * \author Ewen C. Bastien B.
 * \version 1.0
 * \date 22/11/2015
 *
 * Les différentes fonction nécessaire à la résolution d'une grille de ruzzle
 *
 ***********************************************/

#include <string.h>
#include <ctype.h>
#include "../include/ruzzle.h"
#include "../include/liste.h"
/**
	\brief Fonction d'initialisation globale

	\param char entree[] les lettres de la grille du ruzzle.
	\param cell sortie[N][N] la transformé en tableau de entree[].
	\param FILE * dico le dictionnaire complet
	\param FILE * output le fichier où seront placé les mot possible.

	\return Renvoit un code d'erreur si besoin, 0 sinon.

	Initialise la grille avec les lettre passées en paramètre et verifie que les fichiers soient accessibles.
**/
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
 * \brief Crée un dictionaire élagué
 *
 * \param cell ruzzle[N][N] : matrice du ruzzle
 * \param FILE * dico : dictionnaire complet
 * \return renvoie toujours 0 (pourait être amélioré en renvoiyant un code d'erreur)
 *
 * Crée un nouveau dictionnaire appelé nexdico.txt qui ne contiend que les mot dont les lettres sont présentes dans la grille.
 * Cette fonction permet de réduire la taille du fichier parcouru de 3.6Mo à environ 800Ko.
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
 * \brief Trouve la lettre autour de la position passée en paramètre
 *
 * \param char c charactère recherché
 * \param coord * pos position autour de laquel chercher
 * \param cell ruzzle[N][N] : grille du ruzzle
 * \return retourne true si la lettre à été trouvé, false sinon.
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
 * \brief Ajoute un mot et son score dans une liste triée
 *
 * \param char * mot : mot à enregistré
 * \param int score : score du mot
 *
 * Ajoute le mot et son score dans une liste doublement chainée.
 * l'insertion est effectué de sorte à garder un ordre décroisant.
 *
 ***********************************************/
void add_word(char * mot, int score)
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
 * \brief Ajoute le score de la lettre courante
 *
 * \param cell ruzzle[N][N] grille du ruzzle
 * \param coord pos position actuel
 * \param t_score * score pointeur sur le score du mot que l'on cherche
 *
 * ajouter_score ajoute le score de la lettre qui se trouve dans
 * la grille a la position de type coord en parametre et l'ajoute
 * au score (comptabilise également les multiplicateurs de mots).
 *
 ***********************************************/
void add_score (cell ruzzle[N][N], coord pos, t_score * score)
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
 * \brief Réinitialise le statut visité de chaque case
 *
 * \param cell ruzzle[N][N] grille du ruzzle
 *
 * init_visit prend la grille du ruzzle en paramètre et réinitialise
 * le booléen qui indique le passage ou non sur une case en le passant à false.
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
 * \brief Cherche un mot dans la grille
 *
 * \param cell ruzzle[N][N] grille du ruzzle
 * \param char mot[] un mot du dictionnaire à chercher dans la grille
 *
 * find_word prend en paramètre la grille du ruzzle et un mot,
 * cherche le mot a l'aide d'autre fonction et l'inscrit dans
 * la liste des solution avec son score.
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
				add_score(ruzzle, coordonnee, &score);
			}
		}
	}
	for(int i=1; i<strlen(mot) && possible; i++)
	{
		if(find_letter(mot[i],&coordonnee,ruzzle))
		{
			if(strlen(mot)>1)
            {
                add_score(ruzzle, coordonnee, &score);
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
		    add_word(mot, score.point*score.multi);
		}
	}
	init_visited(ruzzle);
}


/********************************************//**
 * \brief Enregiste la liste des mots possible dans un fichier externe
 *
 ***********************************************/
void print_list()
{
    char mot[20];
    int score;
    FILE * out=fopen("output.txt","w");
    if(!liste_vide())
    {
        en_tete();
        while(!hors_liste())
        {
            valeur_elt(&mot,&score);
            fprintf(out,"%i - %s\n",score,mot);
            suivant();
        }
    }
    fclose(out);
}
