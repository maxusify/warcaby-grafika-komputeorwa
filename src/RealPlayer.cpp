#include "../include/RealPlayer.h"
#include "../include/GameState.h"

/**
 * Konstruktor klasy RealPlayer
 */
RealPlayer::RealPlayer(bool topSideOfBoard, CheckersBoard *board, Button *buttons): Player(topSideOfBoard, board, buttons)
{
    selectingState = false;
}

/**
 * Destruktor klasy RealPlayer
 */
RealPlayer::~RealPlayer()
{
    delete Board;
    Board = NULL;
    delete boardButtons;
    boardButtons = NULL;
}

/**
 * Wykonuje ruch
 */
bool RealPlayer::makeMove(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) 
    {
        // Selecting state for inital piece
        if (!selectingState) 
        {
            killWasMade = false;
            for (int index=0; index<TOTAL_BUTTONS; index++) 
            {
                if (boardButtons[index].insideButton(BUTTON_WIDTH, BUTTON_HEIGHT)) 
                {
                    // Player selects a piece to move //
                    selectPiece(
                        boardButtons[index].getButtonPointX()/80, 
                        boardButtons[index].getButtonPointY()/80
                    );

                    break;
                }
            }
        }
        // Selecting for the piece to be moved
        else
        {
            for (int index=0; index<TOTAL_BUTTONS; index++) 
            {
                if (boardButtons[index].insideButton(BUTTON_WIDTH,BUTTON_HEIGHT)) 
                {
                    // Player selects where the piece should move //
                    if (selectedLocationIsValid(
                        currentIndex,boardButtons[index].getButtonPointX()/80, 
                        boardButtons[index].getButtonPointY()/80, false))
                    {
                        movePiece(
                            Board->virtualBoard, 
                            team, 
                            currentIndex, 
                            boardButtons[index].getButtonPointX()/80, 
                            boardButtons[index].getButtonPointY()/80
                        );

                        Board->turnHighLightOff();
                        
                        if (killWasMade) 
                        {
                            selectPiece(team[killerPeiceIndex].x, team[killerPeiceIndex].y);

                            if (Board->validLocations.size() == 0) 
                            {
                                selectingState = false;
                                Board->turnHighLightOff();
                                return true;
                            }
                        }

                        if (!killWasMade) 
                        {
                            return true;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }

    return false;
}

// SELECT PIECE //
// When a piece hasn't been selected yet, and the button currently selected doesn't have a piece inside //
void RealPlayer::selectPiece(int x, int y)
{
    if (sameTeam(Board->virtualBoard[x][y], TEAM_NUMBER))
    {
        currentIndex = pieceTeamIndexByXY(x, y);
        Board->turnHighLightOn(x, y);
        highlightValidMoves();
        selectingState = true;
        cout << "Selected piece is:\t(" << x << ", " << y << ")" << endl;
    }
    else
    {
        cout << "Piece isn't apart of your team" << endl;
    }
}

/**
 * Sprawdza czy wybrana lokalizacja do ruchu jest prawidłowa
 */
bool RealPlayer::selectedLocationIsValid(int currentIndex, int x, int y, bool forHighlight) 
{
    bool locationIsValid = false;

    if (Board->virtualBoard[x][y] == EMPTY_PIECE) 
    {
        // Przypadek w którym poruszamy się w okół centrum kwadratu 3 na 3...
        if (
            abs(x - team[currentIndex].x) == 1 && 
            abs(y - team[currentIndex].y) == 1 && 
            !killWasMade
        ) {
            // ...i pionek jest królem
            if (team[currentIndex].isKing()) 
            {
                locationIsValid = true;
            }

            // ...i pionek nie jest królem
            else if (y - team[currentIndex].y == ONE) 
            {
                locationIsValid = true;
            }
        }
        // Przypadek w którym poruszamy się w okół centrum kwadratu 5 na 5...
        else if (
            abs(x - team[currentIndex].x) == 2 && 
            abs(y - team[currentIndex].y) == 2 && 
            sameTeam(Board->virtualBoard[(x + team[currentIndex].x)/2][(y + team[currentIndex].y)/2],ENEMY_TEAM_NUMBER)
        ) {
            // ...i pionek jest królem
            if (team[currentIndex].isKing()) 
            {
                locationIsValid = true;
            }

            // ...i pionek nie jest królem
            else if (y - team[currentIndex].y == 2*ONE) 
            {
                locationIsValid = true;
            }
        }
    }
    // Przypadek w którym wybieramy inny pionek (nasz)
    else if (sameTeam(Board->virtualBoard[x][y],TEAM_NUMBER) && !forHighlight && !killWasMade)
    {
        Board->turnHighLightOff();
        selectPiece(x, y);
        locationIsValid = false;
    }

    if (!locationIsValid && !forHighlight) 
    {
        cout << "Nie można się tu przemieścić." << endl;
    }
    else if(!killWasMade)
    {
        selectingState = false;
    }

    return locationIsValid;
}

/**
 * Podświetla prawidłowe ruchy
 */
void RealPlayer::highlightValidMoves() 
{
    int x, y;

    for (int i = -2; i <=2; i++)
    {
        x = team[currentIndex].x + i;

        for (int j = -2; j <=2; j++)
        {
            y = team[currentIndex].y + j;
            
            if (x >= 0 && x < 8 && y >= 0 && y < 8) 
            {
                if (selectedLocationIsValid(currentIndex,x, y, true)) 
                {
                    PointPosition pointToHighlight = {
                        x,
                        y
                    };
                    
                    Board->validLocations.push_back(pointToHighlight);
                }
            }
        }
    }
}





