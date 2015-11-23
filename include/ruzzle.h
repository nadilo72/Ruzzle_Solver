#include <stdio.h>
#include <stdbool.h>

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

int init(char [], cell [N][N], FILE * , FILE * );
int create_new_dico(cell [N][N], FILE * );
bool find_letter(char, coord * , cell [N][N]);
void ajouter_mot(char * , int );
void ajouter_score (cell [N][N], coord , t_score * );
void init_visited (cell [N][N]);
void find_word(cell [N][N], char []);
int print_list(FILE * );
