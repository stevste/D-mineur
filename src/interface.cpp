#include "interface.h"

Interface::Interface(int screenW, int height)
{
    mines = STANDARD_NB_MINES;

    int w = screenW / 20;
    int h = height / 2;

    rectTime.x = 0;
    rectTime.y = 0;
    rectTime.w = w;
    rectTime.h = h;

    rectMine.x = 0;
    rectMine.y = h;
    rectMine.w = w;
    rectMine.h = h;

    resetButton.x = (screenW/2) - (screenW/30);
    resetButton.y = 0;
    resetButton.w = screenW/15;
    resetButton.h = screenW/15;
}

void Interface::gagnance()
{
    if (mines <= 0)
    {
        SDL_Event gagne;
        gagne.type = SDL_USEREVENT;
        gagne.user.code = YOUWIN;
        SDL_PushEvent(&gagne);
    }
}

bool Interface::isClickOnButton(int x, int y)
{
    return (x > resetButton.x && x < (resetButton.x + resetButton.w) && y < resetButton.h);
}

void Interface::startTimer()
{
    timer.start();
}

void Interface::pauseTimer()
{
    timer.pause();
}

void Interface::updateNbMines(bool IsFalgSet)
{
    if (IsFalgSet)
    {
        mines--;
    }
    else
    {
        mines++;
    }
}

void Interface::draw(SDL_Renderer *renderer, TTF_Font *font, spriteSheet *icones)
{
    SDL_Color color = {255, 0, 0, SDL_ALPHA_OPAQUE};
    std::string texMine = std::to_string(mines);
    std::string textTime = std::to_string(timer.getTick()/1000);

    minesLeft.LoadTextureFromTexte(renderer, color, font, texMine);
    textTimer.LoadTextureFromTexte(renderer, color, font, textTime);

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &resetButton);
    icones->draw(renderer, &resetButton, 0, 1);

    minesLeft.draw(renderer, &rectMine);
    textTimer.draw(renderer, &rectTime);
}

void Interface::reset()
{
    timer.stop();
    mines = STANDARD_NB_MINES;
}

Interface::~Interface()
{

}