#include <stdio.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 40

//1. Underpopulation:	Any live cell with fewer than 2 live neighbours dies 
//2. Equilibrium:	Any live cell with 2 or 3 neighbours lives on to the next generation
//3. Overpopulation:	Any live cell with more than 3 live neighbours dies
//4. Reproduciton: 	Any dead cell with exactly 3 live neighbours becomes a live cell

void printgame(char a[][WIDTH])
{
    for(int i = 0; i < HEIGHT; i++)
    {
	for(int j = 0; j < WIDTH; j++)
	{
	    printf("%c", a[i][j]);
	}
	printf("\n");
    }
    printf("\n");
}


int main(void)
{
    char grid[HEIGHT][WIDTH], next_grid[HEIGHT][WIDTH];
    
    //plain grid
    for(int i = 0; i < HEIGHT; i++)
    {
	for(int j = 0; j < WIDTH; j++)
	{
	    grid[i][j] = '.';
	}
    }
    
    //seed
    grid[20][40] = '#';
    grid[21][40] = '#';
    grid[22][40] = '#';

    int i = 0, j = 0, gens = 0;

    printgame(grid);

    for(gens = 0; gens < 10; gens++){
	for(i = 0; i < HEIGHT; i++)
	{
	    for(j = 0; j < WIDTH; j++)
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

			if(ni >= 0 && ni < HEIGHT && nj >= 0 && nj < WIDTH && grid[ni][nj] == '#'){
			    neighbour++;
			}
		    }
		}		    

		//rules
		if(grid[i][j] == '#' && (neighbour == 2 || neighbour == 3)){
		    next_grid[i][j] = '#'; //equilibrium
		}
		else if(grid[i][j] == '.' && neighbour == 3){
		    next_grid[i][j] = '#'; //reproductiuon
		}
		else{
		    next_grid[i][j] = '.'; //includes underpopulation, overpopulation and nothing
		}
	    }
	}
	memcpy(grid, next_grid, sizeof(grid));

       printgame(next_grid);
    }
}


