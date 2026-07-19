#ifndef SEEDS_H
#define SEEDS_H

#define WIDTH 80
#define HEIGHT 40

#define DEAD '.'
#define ALIVE '#'



typedef struct {
    char grid[HEIGHT][WIDTH];
    int alive;
} Seed;

Seed initialize_seed(const char *seed);

#endif
