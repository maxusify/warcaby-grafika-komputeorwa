#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

enum Directions {
    LEFT,
    RIGHT,
    BACK_LEFT,
    BACK_RIGHT
};

using namespace std;

class Piece
{
public:
    int x;
    int y;
    int potential;
    int directionValues[4] = {-999, -999, -999, -999};
    Directions bestDirection;

    Piece();
    void setPoint(int, int);
    bool isKing();
    void makeKing();
    void findBestDirection();
    void findLargestPotenial();

private:
    bool king;
};

#endif /* PIECE_H */
