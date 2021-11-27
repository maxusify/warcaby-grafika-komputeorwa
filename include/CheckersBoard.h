#ifndef CHECKERSBOARD_H
#define CHECKERSBOARD_H

#include <vector>
#include <iostream>
#include "Engine.h"
#include "Button.h"

/** \struct PointPosition
 *  \brief Uproszczona struktura przechowująca pozycję punktu.
 */
struct PointPosition 
{
    int x;
    int y;
};

/** \class CheckersBoard
 *  \brief klasa reprezentująca planszę do warcabów
 */ 
class CheckersBoard 
{
public:
    friend ostream & operator << (ostream &, CheckersBoard &);
    vector<vector<int>> virtualBoard;
    vector<PointPosition> validLocations;

    CheckersBoard();
    ~CheckersBoard();

    void drawBoard();
    void drawHighlights();
    void turnHighLightOn(int,int);
    void turnHighLightOff();
    void drawBoardPeices(int, int, Button*);
    bool emptyBoard();

private:
    bool highLight;
    PointPosition highLightSelected;
};

#endif /* CHECKERSBOARD_H */
