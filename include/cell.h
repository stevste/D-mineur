#ifndef DEF_CELL
#define DEF_CELL

#include "spriteSheet.h"

#define MINE -1
#define MINE_REVEAL 1
#define FLAG_SET 2

class cell
{
private:
    SDL_Rect rect;
    Image number;
    bool revealed;
    bool flaged;
    int8_t id;

public:
    cell(SDL_Rect rectRef);
    void initNumber(SDL_Renderer *renderer, TTF_Font *font);

    int getId();
    void increaseId();
    bool placeMine(bool safePlace);

    bool setState(SDL_MouseButtonEvent button);
    bool revealForBacktrack();

    void draw(SDL_Renderer *renderer, spriteSheet *icones, bool isGameOver);
    void reset();

    ~cell();
};

#endif