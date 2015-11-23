
/********************************************//**
 * \file liste.c
 * \brief Programme de gestion d'une liste
 * \author Ewen C. Bastien B.
 * \version 1.0
 * \date 22/11/2015
 *
 * Gestion d'une liste doublement chainée contenant une chaine de caractère et un entier
 *
 ***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Déclaration de la structure des éléments de la liste */

/********************************************//**
 * \brief Structure de donnée formant un élément de la liste
 *
 ***********************************************/
typedef struct element
{
    char word[20];                              /**< Chaine de caractère enregistré dans l'élément de la chaine  */
    int score;                                  /**< Score enregistré dans l'élément de la chaine */
    struct element * pred;                      /**< Pointeur vers l'élément précedent */
    struct element * succ;                      /**< Pointeur vers l'élément suivant */
}t_element;

/* Déclaration des indices de drapeau et d'élément courant */
t_element * drapeau;                            /**< Pointeur sur l'élément initial de la liste. */
t_element * ec;                                 /**< Pointeur sur l'élément courant de la liste. */


/********************************************//**
 * \brief Initialise la liste à vide
 *
 ***********************************************/
void init_liste(void)
{
	drapeau = malloc(sizeof(t_element));
	drapeau -> pred = drapeau;
	drapeau -> succ = drapeau;
	ec = drapeau;
}


/********************************************//**
 * \brief Fonction permettant de savoir si la liste contient au moins un element.
 *
 * \return Renvoi un booléen à vrai si la liste est vide, faux sinon.
 *
 ***********************************************/
bool liste_vide(void)
{
	return (drapeau->succ==drapeau);
}


/********************************************//**
 * \brief Verifie si on se trouve encore dans la liste
 *
 * \return Renvoi un booleen à vrai si l'element courant est hors de la liste, faux sinon.
 *
 ***********************************************/
bool hors_liste(void)
{
	return(ec==drapeau);
}


/********************************************//**
 * \brief Positionne en tete de la liste.
 *
 ***********************************************/
void en_tete(void)
{
	if(!liste_vide())
		ec = drapeau->succ;
}


/********************************************//**
 * \brief Positionne en queue de la liste.
 *
 ***********************************************/
void en_queue(void)
{
	if(!liste_vide())
		ec = drapeau->pred;
}


/********************************************//**
 * \brief Positionne sur l'element suivant.
 *
 ***********************************************/
void suivant(void)
{
	if(!hors_liste())
		ec = ec->succ;
}


/********************************************//**
 * \brief Renvoi les valeurs comprises dans l'element courant.
 *
 * \param mot : Le mot enregistré dans la liste
 * \param score : Le score enregistré dans la liste
 *
 ***********************************************/
void valeur_elt(char mot[20],int * score)
{
	if(!hors_liste())
        strcpy(mot,ec->word);
		*score = ec->score;
}


/********************************************//**
 * \brief Ajoute un nouvel élément a droite de l'elt courant
 *
 * \param inWord : Mot à ajouter
 * \param score : Score à ajouter
 *
 ***********************************************/
void ajout_droit(char * inWord,int score)
{
	t_element * new;
	if(liste_vide() || !hors_liste())
	{
		new = malloc(sizeof(t_element));
		strcpy(new->word,inWord);
		new->score = score;
		new->pred = ec;
		new->succ = ec->succ;
		ec->succ->pred=new;
		ec->succ=new;
		ec=new;
	}
}


/********************************************//**
 * \brief Ajoute un nouvel élément a gauche de l'elt courant
 *
 * \param inWord : Mot à ajouter
 * \param score : Score à ajouter
 *
 ***********************************************/
void ajout_gauche(char * inWord,int score)
{
	t_element * new;
	if(liste_vide() || !hors_liste())
	{
		new = malloc(sizeof(t_element));
		strcpy(new->word,inWord);
		new->score = score;
		new->pred = ec->pred;
		new->succ = ec;
		ec->pred->succ=new;
		ec->pred=new;
		ec=new;
	}
}
