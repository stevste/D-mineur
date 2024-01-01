#include "grid.h"

Grid::Grid(int w, int h)
{
    width = w;
    height = h;
    cellSize = SCREEN_WIDTH/w;
    offSety = (SCREEN_HEIGHT/2) - (height*cellSize/2);

    for (int i = 0; i < width; i++)
    {
        std::vector<cell> line;

        for (int j = 0; j < height; j++)
        {
            SDL_Rect refRect = {i*cellSize, j*cellSize + offSety, cellSize, cellSize};
            cell newCell(refRect);
            line.push_back(newCell);
        }

        cells.push_back(line);
    }
}

bool Grid::isValidCase(int i, int j)
{
    if (i >= 0 && j >= 0 && i < width && j < height)
    {
        return true;
    }
    
    return false;
}

void Grid::revealBacktrack(int cellX, int cellY)
{
    for (int8_t i = -1; i <= 1; i++)
    {
        for (int8_t j = -1; j <= 1; j++)
        {
            if (isValidCase(cellX+i, cellY+j))
            {
                if(cells[cellX+i][cellY+j].revealForBacktrack())
                {
                    revealBacktrack(cellX+i, cellY+j);
                }
            }
        }
    }
}

bool Grid::isClickOnGrid(int mouseY)
{
    return (mouseY >= offSety && mouseY <= (SCREEN_HEIGHT - offSety));
    
}

int Grid::getOffset()
{
    return offSety;
}

void Grid::getCellFromClick(int *x, int *y)
{
    *x = *x/cellSize;
    *y = (*y - offSety)/cellSize;
}

void Grid::generate(SDL_Renderer *renderer, TTF_Font *font, int startX, int startY)
{
    srand(time(NULL));
    int nbMines = 99;

    do
    {
        int x = rand() % width;
        int y = rand() % height;

        bool safePlace = false;

        for (int8_t i = -1; i <= 1; i++)
        {
            for (int8_t j = -1; j <= 1; j++)
            {
                if (x == startX+i && y == startY+j)
                {
                    safePlace = true;
                    break;
                }
            }

            if (safePlace)
            {
                break;
            }
        }

        if (cells[x][y].placeMine(safePlace))
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (isValidCase(x+i, y+j))
                    {
                        if (cells[x+i][y+j].getId() != -1)
                        {
                            cells[x+i][y+j].increaseId();
                        }
                    }
                }
            }

            nbMines--;
        }

    } while (nbMines);

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            cells[i][j].initNumber(renderer, font);
        }   
    }
}

void Grid::update(SDL_MouseButtonEvent button, int cellX, int cellY)
{
    if (cells[cellX][cellY].setState(button) && cells[cellX][cellY].getId() == 0)
    {
        revealBacktrack(cellX, cellY);
    }
}

void Grid::draw(SDL_Renderer *renderer, spriteSheet *icone, bool isGameOver)
{
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            cells[i][j].draw(renderer, icone, isGameOver);
        }
    }
}

void Grid::reset()
{
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            cells[i][j].reset();
        }   
    }
}

Grid::~Grid()
{
    for (size_t i = (width-1); i >= 0; i--)
    {
        for (size_t j = 0; j < height; j++)
        {
            cells[i].pop_back();
        }
        cells.pop_back();
    }
}