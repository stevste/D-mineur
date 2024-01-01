#ifndef DEF_IMG
#define DEF_IMG

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Image
{
public:
    Image();
    Image(SDL_Renderer *renderer, std::string path);
    ~Image();

    SDL_Texture* getTexture();
    void getSize(int *w, int *h);
    int getWidth();
    int getHeight();

    void LoadTexture(SDL_Renderer *renderer, std::string path);
    void LoadTextureFromTexte(SDL_Renderer *renderer, SDL_Color textColor, TTF_Font *font, std::string text = "Lorem Ipsum");
    void free();
    void draw(SDL_Renderer *renderer, SDL_Rect *drect, SDL_Rect *srect = NULL);

private:
    SDL_Texture *texture;
    int imgWidth;
    int imgHeight;
};

#endif