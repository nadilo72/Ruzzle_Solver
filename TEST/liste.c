/* Mise en oeuvre par pointeurs d'une liste d'entiers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Déclaration de la structure des éléments de la liste */

typedef struct element{char word[20];int score;struct element * pred;struct element * succ;}t_element;
/* Déclaration des indices de drapeau et d'élément courant */
t_element * drapeau;
t_element * ec;

void init_liste(void)
/* Initialise la liste à vide */
{
	drapeau = malloc(sizeof(t_element));
	drapeau -> pred = drapeau;
	drapeau -> succ = drapeau;
	ec = drapeau;
}

int liste_vide(void)
/* Rend vrai si la liste est vide, faux sinon */
{
	return (drapeau->succ==drapeau);
}

int hors_liste(void)
/* Rend vrai si l'elt courant est hors de la liste, faux sinon */
{
	return(ec==drapeau);
}

void en_tete(void)
/* Positionne en tete de la liste */
{
	if(!liste_vide())
		ec = drapeau->succ;
}

void en_queue(void)
/* Positionne en queue de la liste */
{
	if(!liste_vide())
		ec = drapeau->pred;
}

void precedent(void)
/* Positionne sur l'elt precedent*/
{
	if(!hors_liste())
		ec = ec->pred;
}

void suivant(void)
/* Positionne sur l'elt suivant*/
{
	if(!hors_liste())
		ec = ec->succ;
}

void valeur_elt(char* mot,int * score)
/* Renvoie dans e la veleur de l'elt courant */
{
	if(!hors_liste())
        mot= ec->word;
		*score = ec->score;
}


void oter_elt(void)
/* Supprime l'elt courant et positionne sur le precedent */
{
	t_element * temp;
	if(!hors_liste())
	{
		ec->succ->pred = ec->pred;
		ec->pred->succ=ec->succ;
		temp = ec;
		precedent();
		free(temp);
	}
}

void ajout_droit(char word[20],int score)
/* Ajoute v a droite de l'elt courant */
{
	t_element * new;

	if(liste_vide() || !hors_liste())
	{
		new = malloc(sizeof(t_element));
		strcpy(new->word,word);
		new->score = score;
		new->pred = ec;
		new->succ = ec->succ;
		ec->succ->pred=new;
		ec->succ=new;
		ec=new;
	}
}

void ajout_gauche(char word[20],int score)
/* Ajoute v a gauche de l'elt courant */
{
	t_element * new;

	if(liste_vide() || !hors_liste())
	{
		new = malloc(sizeof(t_element));
		strcpy(new->word,word);
		new->score = score;
		new->pred = ec->pred;
		new->succ = ec;
		ec->pred->succ=new;
		ec->pred=new;
		ec=new;
	}
}
