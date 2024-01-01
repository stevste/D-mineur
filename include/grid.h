#ifndef DEF_GRID
#define DEF_GRID

#include <vector>
#include <ctime>
#include "cell.h"
#include "spriteSheet.h"


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 728

class Grid
{
private:
    int width;
    int height;
    int cellSize;
    std::vector<std::vector<cell>> cells;
    int offSety;

    bool isValidCase(int i, int j);
    void revealBacktrack(int cellX, int cellY);

public:
    Grid(int w, int h);
    ~Grid();

    bool isClickOnGrid(int mouseY);
    int getOffset();
    void getCellFromClick(int *x, int *y);

    void generate(SDL_Renderer *renderer, TTF_Font *font, int startX, int startY);
    void update(SDL_MouseButtonEvent button, int cellX, int cellY);
    void draw(SDL_Renderer *renderer, spriteSheet *icone, bool isGameOver);
    void reset();
};

#endif