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

int info_case(int ** tab, int x, int y){
    return tab[x][y];
}

// void remplirTableau(int ** tab){
//     int r = 0;
//     int c = 0;
//     for(r = 0; r < 5; r++)
//         for(c = 0; c < 5; c++)
//             tab[r][c] = 100;
// }

int main()
{
    int TMAX = init_BoardSize();
    int ** tab = init_Board(TMAX);

    // tab[2][2] = 52;
    // printf("La valeur est de %d", tab[2][2]);
    // Fonction juste pour tester

    display(tab, TMAX);
    printf("Valeur est %d", info_case(tab, 0, 0));

    return 0;
}