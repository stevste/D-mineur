#ifndef DEF_INTERFACE
#define DEF_INTERFACE

#include "spriteSheet.h"
#include "timer.h"

#define STANDARD_NB_MINES 99
#define YOUWIN 10

class Interface
{
private:
    SDL_Rect resetButton;
    SDL_Rect rectTime;
    SDL_Rect rectMine;
    Timer timer;
    Image minesLeft;
    Image textTimer;
    int8_t mines;

    void gagnance();
public:
    Interface(int screenW, int height);
    ~Interface();
    
    bool isClickOnButton(int x, int y);

    void startTimer();
    void pauseTimer();
    void updateNbMines(bool IsFalgSet);

    void draw(SDL_Renderer *renderer, TTF_Font *font, spriteSheet *icones);
    void reset();
};

#endif