#include "cell.h"

cell::cell(SDL_Rect rectRef)
{
    rect = rectRef;
    revealed = false;
    flaged = false;
    id = 0;

    rect.w--;
    rect.h--;
}

void cell::initNumber(SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_Color textColor = {0, 0, 0, SDL_ALPHA_OPAQUE};

    switch (id)
    {
    case 1:
        textColor.b = 255;
        break;
    
    case 2:
        textColor.g = 128;
        break;

    case 3:
        textColor.r = 255;
        break;

    case 4:
        textColor.b = 128;
        break;

    case 5:
        textColor.r = 128;
        break;

    default:
        break;
    }

    if (id > 0)
    {
        number.LoadTextureFromTexte(renderer, textColor, font, std::to_string(id));
    }
}

int cell::getId()
{
    return id;
}

void cell::increaseId()
{
    id++;
}

bool cell::placeMine(bool safePlace)
{
    if (id != MINE && !safePlace)
    {
        id = MINE;
        return true;
    }
    
    return false;
}

bool cell::setState(SDL_MouseButtonEvent button)
{
    SDL_Event CellEvent;
    CellEvent.type = SDL_USEREVENT;

    if (button.button == SDL_BUTTON_LEFT && !revealed && !flaged)
    {
        revealed = true;

        if (id == -1)
        {
            CellEvent.user.code = MINE_REVEAL;
            SDL_PushEvent(&CellEvent);
        }

        return true;
    }
    else if (button.button == SDL_BUTTON_RIGHT && !revealed)
    {
        flaged = !flaged;

        CellEvent.user.code = FLAG_SET;
        CellEvent.user.data1 = &flaged;
        SDL_PushEvent(&CellEvent);

        return true;
    }
    
    return false;
}

bool cell::revealForBacktrack()
{
    if (id != MINE && !revealed && !flaged)
    {
        revealed = true;

        return (id == 0);
    }

    return false;
}

void cell::draw(SDL_Renderer *renderer, spriteSheet *icone, bool isGameOver)
{
    if (revealed)
    {
        if (id == MINE)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
            icone->draw(renderer, &rect, 0, 0);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
            number.draw(renderer, &rect, NULL);
        }
    }
    else if (flaged)
    {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
        icone->draw(renderer, &rect, 1, 0);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    if (isGameOver)
    {
        if (flaged && id != MINE)
        {
            icone->draw(renderer, &rect, 1, 1);
        }
        else if(!flaged && !revealed && id == -1)
        {
            icone->draw(renderer, &rect, 0, 0);
        }
    }
}

void cell::reset()
{
    id = 0;
    revealed = false;
    flaged = false;
    number.free();
}

cell::~cell()
{

}