#include <stdio.h>
#include <stdlib.h>

int init_BoardSize()
{
    int TMAX = 6;
    printf("Entre la taille du goban: ");
    scanf("%d", &TMAX);
    if (TMAX > 6 || TMAX < 1)
    {
        printf("\nLa taille du goban doit etre comprise entre 1 et 6");
        exit(0);
    }
    return TMAX;
}

int ** init_Board(int TMAX)
{
    int ** tab = malloc(TMAX * sizeof(int));
    int i = 0;
    int r = 0;
    int c = 0;

    for(i = 0; i < TMAX; i++)
        tab[i] = malloc(TMAX * sizeof(int));

    for(r = 0; r < TMAX; r++)
        for(c = 0; c < TMAX; c++)
            tab[r][c] = 0;
    return tab; 
}

void display(int ** tab, int TMAX){
    int r = 0;
    int c = 0;
    int graph;

    for (r = 0 ; r < TMAX ; r++ )
	{
		for (c = 0 ; c < TMAX; c++)
		{
			if (c == TMAX - 1)
			{
				printf("%d", tab[r][c]);
			}
			else
			{
				printf("%d--", tab[r][c]);
			}
		}
		if (r < TMAX - 1)
		{
			printf("\n");
            for(graph = 0; graph < TMAX; graph++)
            {
                printf("|  ");
            }     		
			printf("\n");
		}	
	}
    printf("\n");
}

int info_case(int ** tab, int TMAX, int x, int y){
    if(y < 0 || x < 0 || (x < 0 && y < 0) || y > TMAX - 1 || x > TMAX - 1 || (x > TMAX - 1 && y > TMAX - 1))
    {
       return 1;
    }
    else
    {
        return tab[x][y];
    }
}


// int pierre_isoler(int ** tab, int x, int y)
// {
// 	int piece = info_case(tab, x, y);
// 	int up = info_case(tab, x - 1, y);
// 	int down = info_case(tab, x + 1, y);
// 	int right = info_case(tab, x, y + 1);
// 	int left = info_case(tab, x, y - 1);
// 	int liberter = 0;
// 	if(up == 0)
// 	{
// 		liberter += 1;
// 	}
// 	if(down == 0)
// 	{
// 		liberter += 1;
// 	}
// 	if(right == 0)
// 	{
// 		liberter += 1;
// 	}
// 	if(left == 0)
// 	{
// 		liberter += 1;
// 	}
	
// 	if (piece == 1)
// 	{
// 		printf("La pierre Blanche a %d\n", liberter);
// 	}
// 	if (piece == 2)
// 	{
// 		printf("La pierre Noir a %d\n", liberter);
// 	}
// }

int pierre_isoler(int ** tab, int TMAX, int x, int y)
{
	int piece = info_case(tab, TMAX, x, y);
	int up = info_case(tab, TMAX, x - 1, y);
	int down = info_case(tab, TMAX, x + 1, y);
	int right = info_case(tab, TMAX, x, y + 1);
	int left = info_case(tab, TMAX, x, y - 1);
	int liberter = 0;
	if(up == 0)
	{
		liberter += 1;
	}
	if(down == 0)
	{
		liberter += 1;
	}
	if(right == 0)
	{
		liberter += 1;
	}
	if(left == 0)
	{
		liberter += 1;
	}
	
	if (piece == 1)
	{
		printf("La pierre Blanche a %d\n", liberter);
	}
	if (piece == 2)
	{
		printf("La pierre Noir a %d\n", liberter);
	}
}

void AjoutPierre(int ** tab, int x, int y, char couleur[5])
{
    if(couleur == "Noir"){
        tab[x][y] = 2;
    }
    if(couleur == "Blanc"){
        tab[x][y] = 1;
    }
}


int main()
{
    int TMAX = init_BoardSize();
    int ** tab = init_Board(TMAX);

    AjoutPierre(tab, 2, 2, "Blanc");
    AjoutPierre(tab, 0, 1, "Noir");
    

    display(tab, TMAX);
    pierre_isoler(tab, TMAX, 2, 2);

    return 0;
}