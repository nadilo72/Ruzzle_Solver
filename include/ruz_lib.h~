void ajouter_score (cell ruzzle[N][N], coord pos, t_score * score)



void init_visit (cell ruzzle[N][N])


/*	init prend en paramètre, la chaine à l'origine du ruzzle, le tableau
**	de type cell ou on va écrire chaque lettres et ces multiplicateurs
**	et ouvre les fichier du dictionnaire et de sortie des solutions.
*/
int init(char entree[], cell sortie[N][N], FILE * dico, FILE * output)


/*	create_new_dico prend la grille du ruzzle et un fichier
**	ouvert en lecture (le dictionnaire) et regarde pour chaque
**	mot si les lettres de celui-ci sont toutes présentes (le
**	mot est-il faisable avec cette grille ?) et suprime les 
**	mots infaisable.
*/
int create_new_dico(cell ruzzle[N][N], FILE * dico)


/*	find_letter prend en paramètre un caractère, ces coordonnées
**	ainsi que la grille du ruzzle et va chercher si au alentour
**	des coordonnées donné il y a la lettre suiante du mot à
**	vérifié (la lettre c est-elle voisine ?).
*/
void find_letter(char c, coord * coordonnee, cell ruzzle[N][N])


/*	find_word prend en paramètre la grille du ruzzle et un mot,
**	cherche le mot a l'aide d'autre fonction et l'inscrit dans
**	la liste des solution avec son score.
*/
void find_word(cell ruzzle[N][N], char mot[])
