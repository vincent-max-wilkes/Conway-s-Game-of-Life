#include <string.h>
#include <stdlib.h>

#include "seeds.h"


Seed initialize_seed(const char *seed)
{
    Seed result;

    //plain grid
    for(int i = 0; i < HEIGHT; i++)
    {
	for(int j = 0; j < WIDTH; j++)
	{
	    result.grid[i][j] = DEAD;
	}
    }

    int r = HEIGHT/2;
    int c = WIDTH/2;
    
    //random
    if(strcmp(seed, "random") == 0){
	for(int i = 0; i < HEIGHT; i++)
	{
	    for(int j = 0; j < WIDTH; j++)
	    {
		if(rand() % 100 < 20)
		    result.grid[i][j] = ALIVE;
	    }
	}
    }

    //block (still life)
    else if(strcmp(seed, "block") == 0){
	result.grid[r][c] = ALIVE;
	result.grid[r][c+1] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+1][c+1] = ALIVE;

    }

    //beehive (still life)
    else if(strcmp(seed, "beehive") == 0){
	result.grid[r-1][c] = ALIVE;
	result.grid[r-1][c+1] = ALIVE;
	result.grid[r][c-1] = ALIVE;
	result.grid[r+1][c-1] = ALIVE;
	result.grid[r+2][c] = ALIVE;
	result.grid[r+2][c+1] = ALIVE;
	result.grid[r+1][c+2] = ALIVE;
	result.grid[r][c+2] = ALIVE;
    }

    //blinker (oscillator)
    else if(strcmp(seed, "blinker") == 0){
	result.grid[r][c] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+2][c] = ALIVE;
    }

    // toad (oscillator)
    else if(strcmp(seed, "toad") == 0){
	result.grid[r][c+1] = ALIVE;
	result.grid[r][c+2] = ALIVE;
	result.grid[r][c+3] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+1][c+1] = ALIVE;
	result.grid[r+1][c+2] = ALIVE;
    }

    // beacon (oscillator)
    else if(strcmp(seed, "beacon") == 0){
	result.grid[r][c] = ALIVE;
	result.grid[r][c+1] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+1][c+1] = ALIVE;
	result.grid[r+2][c+2] = ALIVE;
	result.grid[r+2][c+3] = ALIVE;
	result.grid[r+3][c+2] = ALIVE;
	result.grid[r+3][c+3] = ALIVE;
    }

    // glider (spaceship)
    else if(strcmp(seed, "glider") == 0){
	result.grid[r][c+1] = ALIVE;
	result.grid[r+1][c+2] = ALIVE;
	result.grid[r+2][c] = ALIVE;
	result.grid[r+2][c+1] = ALIVE;
	result.grid[r+2][c+2] = ALIVE;
    }

    // lightweight spaceship
    else if(strcmp(seed, "lwss") == 0){
	result.grid[r][c+1] = ALIVE;
	result.grid[r][c+2] = ALIVE;
	result.grid[r][c+3] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+1][c+3] = ALIVE;
	result.grid[r+2][c+3] = ALIVE;
	result.grid[r+3][c] = ALIVE;
	result.grid[r+3][c+1] = ALIVE;
	result.grid[r+3][c+2] = ALIVE;
    }

    // acorn
    else if(strcmp(seed, "acorn") == 0){
	result.grid[r][c+1] = ALIVE;
	result.grid[r+1][c+3] = ALIVE;
	result.grid[r+2][c] = ALIVE;
	result.grid[r+2][c+1] = ALIVE;
	result.grid[r+2][c+4] = ALIVE;
	result.grid[r+2][c+5] = ALIVE;
	result.grid[r+2][c+6] = ALIVE;
    }
    return result;
}
