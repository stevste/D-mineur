#ifndef DEF_SPRITE
#define DEF_SPRITE

#include "img.h"

class spriteSheet
{
public:
    spriteSheet();
    spriteSheet(SDL_Renderer *renderer, std::string path, int spriteX, int spriteY);
    SDL_Rect getTile();
    void draw(SDL_Renderer *renderer, SDL_Rect *drect, int tileX, int tileY);
    ~spriteSheet();
private:
    Image *image;
    SDL_Rect tile;
    int nbSpriteX, nbSpriteY;
};

#endif