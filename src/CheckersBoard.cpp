#include "../include/CheckersBoard.h"
#include "../include/GameState.h"
#include "../include/Texture.h"

/**
 * Konstruktor klasy CheckersBoard
 */
CheckersBoard::CheckersBoard()
{
    for (int y = 0; y < 8; y++)
    {
        vector<int> rowVector;

        for (int x = 0; x < 8; x++)
        {
            rowVector.push_back(0);
        }

        virtualBoard.push_back(rowVector);
    }

    highLight = false;
    highLightSelected.x = NULL;
    highLightSelected.y = NULL;
}

/**
 * Destruktor klasy CheckersBoard
 */
CheckersBoard::~CheckersBoard()
{
    virtualBoard.clear();
}

ostream & operator << (ostream & output, CheckersBoard & boardPassed)
{
    output << "========" << endl;
    for (int y=0; y<8; y++) {
        for (int x=0; x<8; x++) {
            if ((y + x) % 2 == 1) {
                output << boardPassed.virtualBoard[x][y];
            }
            else {
                output << " ";
            }
        }
        output << endl;
    }
    return output;
}

/**
 * Włącza podświetlenie
 */
void CheckersBoard::turnHighLightOn(int x,int y){
    highLight = true;
    highLightSelected.x = x * 80;
    highLightSelected.y = y * 80;
}

/**
 * Wyłącza podświetlenie
 */
void CheckersBoard::turnHighLightOff(){
    highLight = false;
    validLocations.clear();
}

/**
 * Rysuje planszę
 */
void CheckersBoard::drawBoard() 
{
    bool indent = false;
    int startX;

    // Kolor planszy (Drugi kolor do pary)
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    for (int y = 0; y < SCREEN_HEIGHT; y += BUTTON_HEIGHT)
    {
        if (indent) 
        {
            startX = BUTTON_WIDTH;
            indent = false;
        }
        else
        {
            startX = 0;
            indent = true;
        }

        for (int x = startX; x < SCREEN_WIDTH; x += 2*BUTTON_WIDTH)
        {
            SDL_Rect redRect = {
                x, 
                y, 
                BUTTON_WIDTH, 
                BUTTON_HEIGHT
            };
            SDL_RenderFillRect(renderer, &redRect);
        }
    }

    drawHighlights();
}

/**
 * Rysuje poðświetlenia na planszy
 */
void CheckersBoard::drawHighlights() 
{
    if (highLight) 
    {
        // Kolor podświetlenia aktywnego pionka
        SDL_SetRenderDrawColor(renderer, 0x12, 0x94, 0x88, 0x0F);
        SDL_Rect outLine = {
            highLightSelected.x, 
            highLightSelected.y, 
            BUTTON_WIDTH, 
            BUTTON_HEIGHT
        };
        SDL_RenderFillRect(renderer, &outLine);
        
        // Kolor podświetlenia możliwych ruchów
        SDL_SetRenderDrawColor(renderer, 0x20, 0xC4, 0xF4, 0x0F);
        for (int indexOfValidMoves = 0; indexOfValidMoves < validLocations.size(); indexOfValidMoves++) {
            SDL_Rect outLineValid = {
                validLocations[indexOfValidMoves].x * 80,
                validLocations[indexOfValidMoves].y * 80, 
                BUTTON_WIDTH, 
                BUTTON_HEIGHT
            };
            SDL_RenderFillRect(renderer, &outLineValid);
        }
    }
}

/**
 * Rysuje pionki na planszy
 */
void CheckersBoard::drawBoardPeices(int x, int y, Button *boardButton)
{
    switch (virtualBoard[x][y]) 
    {
        case RED_PIECE:
            currentSprite = RED_PIECE;
            boardButton->render(currentSprite-1);
            break;
            
        case BLACK_PIECE:
            currentSprite = BLACK_PIECE;
            boardButton->render(currentSprite-1);
            break;
            
        case RED_KING_PIECE:
            currentSprite = RED_KING_PIECE;
            boardButton->render(currentSprite-1);
            break;
            
        case BLACK_KING_PIECE:
            currentSprite = BLACK_KING_PIECE;
            boardButton->render(currentSprite-1);
            break;

        default:
            break;
    }
}
   