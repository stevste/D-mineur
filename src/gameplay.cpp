#include "gameplay.h"

Gameplay::Gameplay(SDL_Renderer *currentRenderer, TTF_Font *currentFont)
{
    grid = new Grid(32, 16);
    icones = new spriteSheet(currentRenderer, "content/icones.png", 2, 2);
    interface = new Interface(SCREEN_WIDTH, grid->getOffset());
    renderer = currentRenderer;
    font = currentFont;

    started = false;
    isGameOver = false;
}

void Gameplay::operator()(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (interface->isClickOnButton(mouseX, mouseY))
        {
            interface->reset();
            grid->reset();
            started = false;
            isGameOver = false;
        }
        else if(grid->isClickOnGrid(mouseY) && !isGameOver)
        {
            grid->getCellFromClick(&mouseX, &mouseY);

            if (!started)
            {
                grid->generate(renderer, font, mouseX, mouseY);
                started = true;
                interface->startTimer();
            }

            grid->update(event->button, mouseX, mouseY);
        }
        
        break;

    case SDL_USEREVENT:
        switch (event->user.code)
        {
        case FLAG_SET:
            interface->updateNbMines(*(bool*)event->user.data1);
            break;
        
        case MINE_REVEAL:
            isGameOver = true;
            interface->pauseTimer();

        case YOUWIN:
            interface->pauseTimer();
        default:
            break;
        }
        break;
    
    default:
        break;
    }
}

void Gameplay::draw()
{
    grid->draw(renderer, icones, isGameOver);
    interface->draw(renderer, font, icones);
}

Gameplay::~Gameplay()
{
    delete interface;
    delete grid;
    delete icones;
}