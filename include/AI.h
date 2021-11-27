#ifndef AI_H
#define AI_H

#include "Player.h"
#include "CheckersBoard.h"

/** class AI
 *  brief klasa reprezentująca sztucznego przeciwnika
 */ 
class AI : public Player
{
public:
    AI(bool, CheckersBoard*, Button*);
    ~AI();
    bool makeMove(SDL_Event *);

private:
    const int OUT_OF_BOUND = -999;
    const int WIN_VALUE = 999;
    const int MAX_DEPTH = 4;

    vector<Piece> enemyTeam;
    int enemyCurrentIndex;

    int findMax(int,int);
    int findMin(int,int);
    int maxValue(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth, Directions direction);
    int minValue(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth, Directions direction);
    int minMove(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth);
    int maxMove(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth);
    bool checkNode(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, Directions direction, bool enemy);
    int valueCalculator(vector<Piece> teamCopy, vector<Piece> enemyTeamCopy);
    void updateTeam(vector<vector<int>> &tempBoard, vector<Piece> &teamCopy, bool enemy);
    void updateKings(vector<vector<int>> &tempBoard, vector<Piece> &teamCopy, bool enemy);
    void getEnemyTeam();
    bool changeWithDirection(int&,int&,Directions, bool);
    bool killCheckArea(vector<vector<int>> tempBoard, int,int,Directions, bool);
    int bestPiece(vector<Piece>);
    int enemyBestPiece(vector<Piece>);
};

#endif /* AI_H */
