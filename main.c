#include <stdio.h>
#include <stdlib.h>


//Permet de definir la taille du tableau
int init_BoardSize()
{
    int TMAX = 6;
    printf("Entre la taille du goban: ");
    scanf("%d", &TMAX);
    if (TMAX > 6 || TMAX < 1)//Definie les limites du tableau
    {
        printf("\nLa taille du goban doit etre comprise entre 1 et 6");
        exit(0);
    }
    return TMAX;
}

//Creer le tableau dynamique a 2 dimension
//Sur Linux j'ai rencontrer une erreur de segmentation lorsque je retire le + 1 de la ligne 23 et 29 du malloc alors que sur windows je n'ai pas ce problème
int ** init_Board(int TMAX)
{
    int ** tab = malloc(TMAX + 1 * sizeof(int)); //Normalement c'est malloc(TMAX * sizeof(int) mais sur linux lorsque je retire le + 1 je reçois une erreur de segmentation alors que sur mac et windows non
    int i = 0;
    int r = 0;
    int c = 0;

    for(i = 0; i < TMAX; i++)
        tab[i] = malloc(TMAX + 1 * sizeof(int)); //Normalement c'est malloc(TMAX * sizeof(int) mais sur linux lorsque je retire le + 1 je reçois une erreur de segmentation alors que sur mac et windows non

    for(r = 0; r < TMAX; r++)
        for(c = 0; c < TMAX; c++)
            tab[r][c] = 0;
    return tab;
}

//Affiche la grille de jeu
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

//Renvoie la piece qui se trouve sur les coordonnée donner (case ciblé) ou si la case est vide
int info_case(int ** tab, int TMAX, int x, int y){
    if(y < 0 || x < 0 || (x < 0 && y < 0) || y > TMAX - 1 || x > TMAX - 1 || (x > TMAX - 1 && y > TMAX - 1))
    {
       return -1;
    }
    return tab[x][y];
}

//Check Les liberté d'une pierre et d'une pierre qui est isolée aussi
int pierreIsoler_liberter(int ** tab, int TMAX, int x, int y)
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
		//printf("La pierre Blanche a %d\n", liberter); Fonction Test
	}
	if (piece == 2)
	{
		//printf("La pierre Noir a %d\n", liberter); //Fonction test
	}
    if (piece == 0)
    {
        liberter = 0;
    }
    return liberter;
}

//Permet d'ajouter des pierres
void AjoutPierre(int ** tab, int x, int y, char couleur[5])
{
    if(couleur == "Noir"){
        tab[x][y] = 2;
    }
    if(couleur == "Blanc"){
        tab[x][y] = 1;
    }
}

int checkCapture(int ** tab, int TMAX, int x, int y){
    int nbLiberter = pierreIsoler_liberter(tab, TMAX, x, y);
    if(nbLiberter == 0)
    {
        tab[x][y] = 0;
    }
}

//Calcule le nombre de pierre
int countPierre(int ** tab, int TMAX, int couleur){
    int r = 0;
    int c = 0;
    int nb = 0;

    for(r = 0; r < TMAX; r++)
    {
        for(c = 0; c < TMAX; c++)
        {
            int pierre = info_case(tab, TMAX, r, c);
            if (pierre == couleur)
            {
                nb += 1;
            }
            
        }
    }
    return nb;
}

//Calcule le nombres de points
int Calcule_Score(int ** tab, int TMAX){
    int r = 0;
    int c = 0;
    int score[2] = {0};

    for (r = 0 ; r < TMAX ; r++ )
	{
		for (c = 0 ; c < TMAX; c++)
		{
			if (info_case(tab, TMAX, r, c) == 1)
            {
                score[0]++;
            }
            if (info_case(tab, TMAX, r, c) == 2)
            {
                score[1]++;
            }
		}
	}
    printf("Score Noir: %d ---- Score Blanc: %d\n", score[0], score[1]);
    if(score[0] > score[1])
    {
       printf("Les Noirs ont gagner\n"); 
    }
    if(score[1] > score[0])
    {
       printf("Les Noirs ont gagner\n"); 
    }
    return *score;
}


//Resolve les problèmes simple qui se gagne en 1 coup peut faire que des problèmes de 1 coup (Le programme rattrape automatiquement les coup non jouer manquant)
//C'est a dire si l'autre pierre a des coup d'avance impossible/illégaux
void Solver(int ** tab, int TMAX){
    int r = 0;
    int c = 0;
    int nbNoir = countPierre(tab, TMAX, 1);
    int nbBlanc = countPierre(tab, TMAX, 2);

    if(nbNoir == nbBlanc || nbNoir < nbBlanc)
    {
        for(r = 0; r < TMAX; r++)
        {
            for(c = 0; c < TMAX; c++)
            {
                int piece = info_case(tab, TMAX, r, c);
                int liberter = pierreIsoler_liberter(tab, TMAX, r, c);
                if(piece == 1)
                {
                    int up = info_case(tab, TMAX, r - 1, c);
                    int down = info_case(tab, TMAX, r + 1, c);
                    int right = info_case(tab, TMAX, r, c + 1);
                    int left = info_case(tab, TMAX, r, c - 1);
                    if(up == 0 && r >= 0)
                    {
                        tab[r - 1][c] = 2;
                        break;
                    }
                    if(down == 0 && r <= TMAX)
                    {
                        tab[r + 1][c] = 2;
                        break;
                    }
                    if(right == 0 && c <= TMAX)
                    {
                        tab[r][c + 1] = 2;
                        break;
                    }
                    if(left == 0 && c >= 0)
                    {
                        tab[r][c - 1] = 2;
                        break;
                    }
                    checkCapture(tab, TMAX, r, c);
                }
            }
        }
    }

    if(nbBlanc < nbNoir)
    {
        for(r = 0; r < TMAX; r++)
        {
            for(c = 0; c < TMAX; c++)
            {
                int piece = info_case(tab, TMAX, r, c);
                int liberter = pierreIsoler_liberter(tab, TMAX, r, c);
                if(piece == 2)
                {
                    int up = info_case(tab, TMAX, r - 1, c);
                    int down = info_case(tab, TMAX, r + 1, c);
                    int right = info_case(tab, TMAX, r, c + 1);
                    int left = info_case(tab, TMAX, r, c - 1);
                    if(up == 0)
                    {
                        tab[r - 1][c] = 1;
                        break;
                    }
                    if(down == 0)
                    {
                        tab[r + 1][c] = 1;
                        break;
                    }
                    if(right == 0)
                    {
                        tab[r][c + 1] = 1;
                        break;
                    }
                    if(left == 0)
                    {
                        tab[r][c - 1] = 1;
                        break;
                    }
                    checkCapture(tab, TMAX, r, c);
                }
            }
        }
    }
}


//renvoie le nombre de liberter des pierre paire
int pierrePaire_liberter(int ** tab, int TMAX, int x, int y, int x2, int y2){
    int liberter = 0;
    liberter = liberter + pierreIsoler_liberter(tab, TMAX, x, y);
    liberter = liberter + pierreIsoler_liberter(tab, TMAX, x2, y2);
    return liberter;
}

//renvoie le nombre de liberter des pierre triplet
int pierreTriplet_liberter(int ** tab, int TMAX, int x, int y, int x2, int y2, int x3, int y3){
    int liberter = 0;
    liberter = liberter + pierreIsoler_liberter(tab, TMAX, x, y);
    liberter = liberter + pierreIsoler_liberter(tab, TMAX, x2, y2);
    liberter = liberter + pierreIsoler_liberter(tab, TMAX, x3, y3);
    return liberter;
}

//Regarde renvoie si la pierre est une pierre isolée ou non
int checkIfPierreIsoler(int ** tab, int TMAX, int x, int y){
    int nbLiberter = pierreIsoler_liberter(tab, TMAX, x, y);
    if (nbLiberter == 4)
    {
        return 1;
    }
    return 0;
}

//renvoie le nombre de liberter d'une pierre non isolée
int liberterPierreNonIsoler(int ** tab, int TMAX, int x, int y){
    int checkIsolee = checkIfPierreIsoler(tab, TMAX, x, y);
    int liberter = 0;
    if(!checkIsolee)
    {
        liberter += pierreIsoler_liberter(tab, TMAX, x, y);
    }
}

//Permet la creation de problème (Je dois l'ameliorer pour qu'il soit mieux et plus simple a utiliser)
void ProblemCreator(int ** tab, int TMAX){
    int r = 0;
    int c = 0;
    int ** tableau = init_Board(TMAX);
    int i = 0;

    for(r = 0; r < TMAX; r++)
    {
        for(c = 0; c < TMAX; c++)
        {
            tab[r][c] = i;
            i++;
            if(i > 5)
            {
                i = 0;
            }
        }
            
    }


    int valeur;

    display(tab, TMAX);
    printf("(Le tableau se remplis de gauche a droite ligne par ligne.)\n");
    printf("(Toutes valeur entrez supérieur a 2 et inférieur a 0 seront par défauts initialiser a 0.)\n");
    printf("Valeur des pièces: Les noir = 2   Les Blanc = 1    Case vide = 0\n");
    printf("Entrez les valeur du tableau:\n");
    for(r = 0; r < TMAX; r++)
    {
        for(c = 0; c < TMAX; c++)
        {
            scanf("%d", &valeur);
            if(valeur > 2 || valeur < 0)
            {
                valeur = 0;
            }
            tab[r][c] = valeur;
        }
            
    }
}


int main()
{
    int TMAX = init_BoardSize();
    int ** tab = init_Board(TMAX);

    ProblemCreator(tab, TMAX);
    printf("\n");

    display(tab, TMAX);
    Solver(tab, TMAX);
    printf("\n");
    display(tab, TMAX);

    Calcule_Score(tab, TMAX);

    return 0;
}



//Pour la question la meilleur structure de données pour ce travail est ce l'ont moi le tableau a 2 dimension (array 2d/matrice 2d) 
//qui permet de facilement gerer et créer un tableau ainsi  que gerer les pièces du jeux

// Il ma manque la question 5 du projet celle de difficulter ***

//Sur Linux j'ai rencontrer une erreur de segmentation lorsque je retire le + 1 de la ligne 23 et 29 du malloc alors que sur windows je n'ai pas ce problème


