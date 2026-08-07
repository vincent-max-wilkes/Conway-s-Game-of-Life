#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 2560 / SCALE
#define HEIGHT 1440 / SCALE
#define SCALE 2
#define STARTCOUNT 50
#define DEAD 0xFFFFFF
#define ALIVE 0x000000

typedef uint32_t grid[HEIGHT][WIDTH];

grid framebuffer;
grid game;
grid next;

void rules(grid game, grid next)
{
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

		    if(ni >= 0 && ni < HEIGHT && nj >= 0 && nj < WIDTH && game[ni][nj] == ALIVE){
			neighbour++;
		    }
		}
	    }		    

	    //rules
	    if(game[i][j] == ALIVE && (neighbour == 2 || neighbour == 3)){
		next[i][j] = ALIVE; //equilibrium
	    }
	    else if(game[i][j] == DEAD && neighbour == 3){
		next[i][j] = ALIVE; //reproductiuon
	    }
	    else{
		next[i][j] = DEAD; //includes underpopulation, overpopulation and nothing
	    }
	}
    }
}

void random_seed(void)
{
    for(int i = 0; i < HEIGHT; i++)
    {
	for(int j = 0; j < WIDTH; j++)
	{
	     if(rand() % 100 < STARTCOUNT)
		 game[i][j] = ALIVE;
	     else
		 game[i][j] = DEAD;
	}
    }
}

void put_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
	return;
    }
    framebuffer[y][x]  = color;
}

void clear(uint32_t color) {
    for(int y = 0; y < HEIGHT; y++)
    {
	for(int x = 0; x < WIDTH; x++)
	{
	    framebuffer[y][x] = color;
	}
    }
}


int main(void)
{

    game_loop:
    srand(time(NULL)); //reset random generation 
    
    random_seed();

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;

    const double target_frame = 1.0 / 60.0; // --> ~0.016, 60 fps

    if (!SDL_Init(SDL_INIT_VIDEO)) {
	fprintf(stderr, "SDL_Init failed; %s \n", SDL_GetError());
	return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(
	"SDL Framebuffer",
	WIDTH * SCALE,
	HEIGHT * SCALE,
	0
    );

    if(window == NULL) {
	fprintf(stderr, "SDL_CreateWindow failed; %s \n", SDL_GetError());
	SDL_Quit();
	return EXIT_FAILURE;
    }

    SDL_MaximizeWindow(window);

    renderer = SDL_CreateRenderer(
	window,
	NULL
    );

    if(renderer == NULL) {
	fprintf(stderr, "SDL_CreateRenderer failed; %s \n", SDL_GetError());
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_FAILURE;
    }

    texture = SDL_CreateTexture(
	renderer,
	SDL_PIXELFORMAT_XRGB8888,
	SDL_TEXTUREACCESS_STREAMING,
	WIDTH,
	HEIGHT
    );

    if(texture == NULL) {
	fprintf(stderr, "SDL_CreateTexture failed; %s \n", SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_FAILURE;
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    uint8_t is_running = 1;

	while(is_running){
	    
	    uint64_t start = SDL_GetPerformanceCounter();

	    /* Poll events */
	    while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
		    is_running = 0;
		}
		if(event.type == SDL_EVENT_KEY_DOWN) {
		    if(event.key.key == SDLK_RETURN) {
			SDL_DestroyTexture(texture);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			goto game_loop;
		    }
		}
	    }

	    clear(DEAD);

	    rules(game, next);

	    for(int i = 0; i < HEIGHT; i++)
	    {
		for(int j = 0; j < WIDTH; j++)
		{
		    if(next[i][j] == ALIVE)
			put_pixel(j, i, ALIVE);
		}
	    }

	    memcpy(game, next, sizeof(game));

	    /* Copy the contents of framebuffer to texture */
	    SDL_UpdateTexture(
		texture,
		NULL,
		framebuffer,
		WIDTH * sizeof(uint32_t) //pitch -> width of texture in bytes
	    );

	    /* Display the window and the renderer */
	    SDL_RenderClear(renderer);
	    SDL_RenderTexture(renderer, texture, NULL, NULL);
	    SDL_RenderPresent(renderer);

	    uint64_t end = SDL_GetPerformanceCounter();

	    double elapsed = (double)(end - start) / (double)SDL_GetPerformanceFrequency();

	    if(elapsed < target_frame) {
		SDL_Delay((target_frame - elapsed) * 1000.0); //sleep until we reach the target of 60 FPS
	    }

	}

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;

}
