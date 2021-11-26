#include "../include/Piece.h"

/**
 * Możliwe ruchy dla króla
 */
Directions kingMoves[4] = {
    LEFT, 
    RIGHT, 
    BACK_LEFT, 
    BACK_RIGHT
};

/**
 * Możliwe ruchy dla pionka
 */
Directions pieceMoves[2] = {
    LEFT, 
    RIGHT
};

/**
 * Konstruktor klasy Piece
 */
Piece::Piece() 
{
    x = 0;
    y = 0;
    potential = -99999999;
    king = false;
}

/**
 * Ustawia lokalizację pionka
 */
void Piece::setPoint (int xLocation, int yLocation) 
{
    x = xLocation;
    y = yLocation;
}

/**
 * Zwraca status bycia królem
 */
bool Piece::isKing() 
{
    return king;
}

/**
 * Zamienia w króla
 */
void Piece::makeKing() 
{
    king = true;
}

/**
 * Wylicza największy potencjał
 */
void Piece::findLargestPotenial()
{
    int largest = directionValues[0];
    
    for (int i = 1; i < 4; i++) 
    {
        if (largest < directionValues[i]) 
        {
            largest = directionValues[i];
        }
    }

    potential = largest;
}

/**
 * Wylicza najlepszy kierunek do ruchu
 */
void Piece::findBestDirection()
{
    int largest = directionValues[0];
    vector<int> largestVector;
    
    for (int i = 1; i < 4; i++) 
    {
        if (largest < directionValues[i]) 
        {
            largest = directionValues[i];
        }
    }
    
    for (int j = 0; j < 4; j++)
    {
        if (largest <= directionValues[j]) 
        {
            largestVector.push_back(j);
        }
    }
    
    srand(static_cast<unsigned int>(time(NULL)));
    int bestIndex = rand() % largestVector.size();
    
    for (int k = 0; k < 4; k++)
    {
        if (kingMoves[k] == largestVector[bestIndex]) 
        {
            bestDirection = kingMoves[k];
        }
    }
}