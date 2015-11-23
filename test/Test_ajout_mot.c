#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Outil.h"

/*

Dans des buts de tests, on a modifié les valeurs de mot et score,
pour testé différents cas de listes initialisé.
Les asserts sont la pour vérifié que les conditions sont respecté et
testé la fiabilité du programme.
A la première version de cette fonction, les tests on révélé des soucis
d'exécution, les mots n'était pas bien placé, cette version estcelle du
programme final, soigné et corrigé.

*/

void main()
{
	char mot[] = "Pomme";
	int score = 10;
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
				Assert1("Impossible, ", score < elem);
				ajout_gauche(mot,score);
				place=true;
			}
			suivant();
		}
		if(!place)
		{
			Assert1("Imposible, le mot est placé !", place==1);
			en_queue();
			ajout_droit(mot,score);
		}
	}
	else
	{
		ajout_droit(mot,score);
	}
}
