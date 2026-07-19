#include <string.h>

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

    //block (still life)
    if(strcmp(seed, "block") == 0){
	result.grid[r][c] = ALIVE;
	result.grid[r][c+1] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+1][c+1] = ALIVE;

	result.alive = 4;

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

	result.alive = 6;
    }

    //blinker (oscillator)
    else if(strcmp(seed, "blinker") == 0){
	result.grid[r][c] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+2][c] = ALIVE;
	
	result.alive = 3;
    }

    // toad (oscillator)
    else if(strcmp(seed, "toad") == 0){
	result.grid[r][c+1] = ALIVE;
	result.grid[r][c+2] = ALIVE;
	result.grid[r][c+3] = ALIVE;
	result.grid[r+1][c] = ALIVE;
	result.grid[r+1][c+1] = ALIVE;
	result.grid[r+1][c+2] = ALIVE;

	result.alive = 6;
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

	result.alive = 8;
    }

    // glider (spaceship)
    else if(strcmp(seed, "glider") == 0){
	result.grid[r][c+1] = ALIVE;
	result.grid[r+1][c+2] = ALIVE;
	result.grid[r+2][c] = ALIVE;
	result.grid[r+2][c+1] = ALIVE;
	result.grid[r+2][c+2] = ALIVE;

	result.alive = 5;
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

	result.alive = 9;
    }

    // acorn
    else if(strcmp(seed, "acorn") == 0){
	int r = HEIGHT/2;
	int c = WIDTH/2;

	result.grid[r][c+1] = ALIVE;

	result.grid[r+1][c+3] = ALIVE;

	result.grid[r+2][c] = ALIVE;
	result.grid[r+2][c+1] = ALIVE;
	result.grid[r+2][c+4] = ALIVE;
	result.grid[r+2][c+5] = ALIVE;
	result.grid[r+2][c+6] = ALIVE;

	result.alive = 7;
    }
    return result;
}
