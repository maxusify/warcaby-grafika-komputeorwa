#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "Player.h"

class CheckersBoard;

class RealPlayer : public Player 
{
public:
    RealPlayer(bool, CheckersBoard*, Button*);
    ~RealPlayer();
    bool makeMove(SDL_Event *);

private:
    void selectPiece(int, int);
    bool selectedLocationIsValid(int, int, int, bool);
    void highlightValidMoves();
    bool selectingState;
};

#endif /* REALPLAYER_H */
