# include <stdio.h>
# include <stdlib.h>


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
