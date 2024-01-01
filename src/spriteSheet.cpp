#include "spriteSheet.h"

spriteSheet::spriteSheet()
{
    image = NULL;
    tile = {0, 0, 0, 0};
    nbSpriteX = 0;
    nbSpriteY = 0;
}

spriteSheet::spriteSheet(SDL_Renderer *renderer, std::string path, int spriteX, int spriteY)
{
    image = new Image(renderer, path);

    nbSpriteX = spriteX;
    nbSpriteY = spriteY;

    int imgW, imgH;
    image->getSize(&imgW, &imgH);

    tile.x = 0;
    tile.y = 0;
    tile.w = imgW/nbSpriteX;
    tile.h = imgH/nbSpriteY;
}

SDL_Rect spriteSheet::getTile()
{
    return tile;
}

void spriteSheet::draw(SDL_Renderer *renderer, SDL_Rect *drect, int tileX, int tileY)
{
    tile.x = tile.w*tileX;
    tile.y = tile.h*tileY;

    image->draw(renderer, drect, &tile);
}

spriteSheet::~spriteSheet()
{
    delete image;
}