#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "seeds.h"
#include "userinput.h"

int count_alive(char grid[HEIGHT][WIDTH]){
    int alive = 0;

    for(int i = 0; i < HEIGHT; i++)
    {
	for(int j = 0; j < WIDTH; j++)
	{
	    if(grid[i][j] == ALIVE){
		alive++;
	    }
	}
    }
    
    return alive;
}

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
    srand(time(NULL)); //reset random generation (not working)
		       //
    int gens = get_gens(argc, argv);
    char *seed = get_seed(argc, argv);

    int current_gen = 0;

    Seed game;
    game = initialize_seed(seed);

    int alive = count_alive(game.grid);
    printgame(game.grid, alive);
    
    char next_grid[HEIGHT][WIDTH] = {0};

    for(int a = 0; a < gens; a++){
	alive = 0;

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
		    alive++;
		}
		else if(game.grid[i][j] == DEAD && neighbour == 3){
		    next_grid[i][j] = ALIVE; //reproductiuon
		    alive++;
		}
		else{
		    next_grid[i][j] = DEAD; //includes underpopulation, overpopulation and nothing
		}
	    }
	}
	if(alive == 0){
	    printf("The civlisation died after %d generations", current_gen);
	    break;
	}

	system("clear"); //clears screen -> animation
	printgame(next_grid, alive);
    
	usleep(400000);

	memcpy(game.grid, next_grid, sizeof(game.grid));
    }
}
