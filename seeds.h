#ifndef SEEDS_H
#define SEEDS_H

#define WIDTH 200
#define HEIGHT 100

#define DEAD '.'
#define ALIVE '#'



typedef struct {
    char grid[HEIGHT][WIDTH];
} Seed;

Seed initialize_seed(const char *seed);

#endif
