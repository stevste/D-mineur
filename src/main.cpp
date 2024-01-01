#include "main.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

int main(int argc, char* args[])
{
    if (!initSDL())
    {
        return 0;
    }

    if (!initGameElement())
    {
        close(NULL);
        return 0;
    }
    
    Gameplay gameplay(renderer, font);
    bool QUIT = false;
    bool start = false;

    while (!QUIT)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_Event event;

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                QUIT = true;
            }
            
            gameplay(&event);
        }

        gameplay.draw();

        SDL_RenderPresent(renderer);
    }

    close(&gameplay);

    return 0;
}

bool initSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Fatal Error: Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Demineur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(!window)
    {
        std::cout << "Fatal Error: Couldn't create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer)
    {
        std::cout << "Fatal Error: Couldn't create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    
    int imgFlag = IMG_INIT_PNG;

    if (!IMG_Init(imgFlag) & imgFlag)
    {
        std::cout << "Fatal Error: Couldn't initialize SDL_Image: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init())
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }

    return true;
}

bool initGameElement()
{
    font = TTF_OpenFont("content/Arial.ttf", 36);

    if (!font)
    {
        return false;
    }

    return true;
}

void close(Gameplay *gameplay)
{
    delete gameplay;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);

    font = NULL;
    renderer = NULL;
    window = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}