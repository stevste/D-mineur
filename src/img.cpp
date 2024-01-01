#include "img.h"

Image::Image()
{
    texture = NULL;
    imgWidth = 0;
    imgHeight = 0;
}

Image::Image(SDL_Renderer *renderer, std::string path)
{
    LoadTexture(renderer, path);
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);
}

SDL_Texture* Image::getTexture()
{
    return texture;
}

void Image::getSize(int *w, int *h)
{
    *w = imgWidth;
    *h = imgHeight;
}

int Image::getWidth()
{
    return imgWidth;
}

int Image::getHeight()
{
    return imgHeight;
}

void Image::free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        imgWidth = 0;
        imgHeight = 0;
    }
}

void Image::LoadTexture(SDL_Renderer *renderer, std::string path)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if(!(loadedSurface))
    {
        std::cout << "ERROR: UNABLE TO LOAD IMAGE : " << path << ": " << IMG_GetError() << std::endl;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (!(texture))
    {
        std::cout << "ERROR: UNABLE TO CREATE TEXTURE : " << path << ": " << IMG_GetError() << std::endl;
    }

    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;
}

void Image::LoadTextureFromTexte(SDL_Renderer *renderer, SDL_Color textColor, TTF_Font *font, std::string text)
{
    free();

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (!surface)
    {
        std::cout << "Couldn't create text from: " << text << std::endl;
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture)
    {
        std::cout << "Couldn't create texture from: " << text << std::endl;
    }

    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);
    
    SDL_FreeSurface(surface);
}

void Image::draw(SDL_Renderer *renderer, SDL_Rect *drect, SDL_Rect *srect)
{
    SDL_RenderCopy(renderer, texture, srect, drect);
}

Image::~Image()
{
    free();
}