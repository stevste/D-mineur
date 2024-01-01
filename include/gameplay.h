#ifndef DEF_GAMEPLAY
#define DEF_GAMEPLAY

#include "grid.h"
#include "interface.h"

class Gameplay
{
private:
    Interface *interface;
    Grid *grid;
    spriteSheet *icones;
    SDL_Renderer *renderer;
    TTF_Font *font;
    bool isGameOver;
    bool started;
public:
    Gameplay(SDL_Renderer *currentRenderer, TTF_Font *currentFont);

    void operator()(const SDL_Event *event);
    void draw();

    ~Gameplay();
};

#endif