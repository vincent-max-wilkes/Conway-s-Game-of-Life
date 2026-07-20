#ifndef SEEDS_H
#define SEEDS_H

#define WIDTH 60
#define HEIGHT 30

#define DEAD '.'
#define ALIVE '#'



typedef struct {
    char grid[HEIGHT][WIDTH];
} Seed;

Seed initialize_seed(const char *seed);

#endif
