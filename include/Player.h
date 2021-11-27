#ifndef PLAYER_H
#define PLAYER_H

#include "CheckersBoard.h"
#include "Piece.h"

using namespace std;
class Button;

/** class Player
 *  brief klasa reprezentująca gracza
 */ 
class Player
{
public:
    vector<Piece> team;
    bool turn;
    bool killWasMade = false;

    Player(bool,CheckersBoard*, Button*);
    ~Player();
    virtual bool makeMove(SDL_Event *);
    void updateTeam();
    void updateKings();

protected:
    int currentIndex;
    bool topSide;
    int ONE;
    int TEAM_NUMBER;
    int ENEMY_TEAM_NUMBER;
    CheckersBoard *Board;
    Button *boardButtons;
    int killerPeiceIndex;

    void movePiece(vector<vector<int>> &, vector<Piece> & ,int, int, int);
    void killPiece(vector<vector<int>> &, int, int);
    void initTeam();
    bool sameTeam(int,int);
    int pieceTeamIndexByXY(int,int);
};


#endif /* PLAYER_H*/
