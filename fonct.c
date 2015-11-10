# include <stdio.h>
# include <stdlib.h>



typedef struct 
{
	unsigned char character;
	unsigned int point;
	unsigned int visited;
} cell;


void check_dico (int *nb_elem, int *exist, int *k, cell sortie[20][100], FILE*dico)
{
	mot[30];
	
	for ()
	{
		
	}
}




void possibility (FILE*dico, cell entre[N][N][3], cell sortie[20][100])
{
	int i;
	int j;
	int k;
	int exist;
	init_sortie (sortie);
	nb_elem = 0;

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			exist = 1;
			k = 0;
			init_visited(entre);
			sortie[nb_elem][k] = entre[i][j];
			nb_elem++;
			k++;
			entre[i][j].visited = 1;
			while (exist != 0)
			{
				check_dico (&nb_elem, &exist, k, sortie, dico);
				take_nei (sortie);
			}
		}
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
