#include <stdio.h>
#include <string.h>

#include "seeds.h"
#include "userinput.h"


void printgame(char a[][WIDTH], int b)
{
    for(int i = 0; i < HEIGHT; i++)
    {
	for(int j = 0; j < WIDTH; j++)
	{
	    printf("%c", a[i][j]);
	}
	printf("\n");
    }
    printf("%d cells are alive!\n\n", b);
}

int main(int argc, char **argv)
{
    int gens = get_gens(argc, argv);
    char *seed = get_seed(argc, argv);

    Seed game;
    game = initialize_seed(seed);
    
    printgame(game.grid, game.alive);

    char next_grid[HEIGHT][WIDTH] = {0};

    for(int a = 0; a < gens; a++){
	game.alive = 0;

	for(int i = 0; i < HEIGHT; i++)
	{
	    for(int j = 0; j < WIDTH; j++)
	    {
		int neighbour = 0;
		for(int di = -1; di < 2; di++)
		{
		    for(int dj = -1; dj < 2; dj++)
		    {
			if(di == 0 && dj == 0){
			    continue;
			}

			int ni = i + di;
			int nj = j + dj;

			if(ni >= 0 && ni < HEIGHT && nj >= 0 && nj < WIDTH && game.grid[ni][nj] == ALIVE){
			    neighbour++;
			}
		    }
		}		    

		//rules
		if(game.grid[i][j] == ALIVE && (neighbour == 2 || neighbour == 3)){
		    next_grid[i][j] = ALIVE; //equilibrium
		    game.alive++;
		}
		else if(game.grid[i][j] == DEAD && neighbour == 3){
		    next_grid[i][j] = ALIVE; //reproductiuon
		    game.alive++;
		}
		else{
		    next_grid[i][j] = DEAD; //includes underpopulation, overpopulation and nothing
		}
	    }
	}
	if(game.alive == 0){
	    break;
	}

	memcpy(game.grid, next_grid, sizeof(game.grid));

       printgame(next_grid, game.alive);
    }
}
