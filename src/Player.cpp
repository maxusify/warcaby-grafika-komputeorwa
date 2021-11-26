#include "../include/Player.h"
#include "../include/CheckersBoard.h"
#include "../include/Button.h"
#include "../include/GameState.h"

/**
 * Konstruktor klasy Player
 */
Player::Player(bool topSideOfBoard, CheckersBoard *board, Button buttons[])
{
    Board = board;
    boardButtons = buttons;
    topSide = topSideOfBoard;
    currentIndex = 0;

    initTeam();

    if (topSideOfBoard) 
    {
        ONE = 1;
        turn = false;
    }
    else
    {
        ONE = -1;
        turn = true;
    }
}

/**
 * Destruktor klasy Player
 */ 
Player::~Player()
{
    team.clear();
    Board = NULL;
    boardButtons = NULL;
}

/**
 * Inicjalizuje drużyny
 */
void Player::initTeam() 
{
    if (topSide) {
        /* ====== DRUZYNA CZARNA ====== */
        // Dodaj na koniec element stworzony normalnym konstruktorem
        // Ustaw pozycje x i y elementu o indeksie n.
        // itd..
        team.push_back(Piece());
        team[0].x = 1;
        team[0].y = 0;

        team.push_back(Piece());
        team[1].x = 3;
        team[1].y = 0;

        team.push_back(Piece());
        team[2].x = 5;
        team[2].y = 0;

        team.push_back(Piece());
        team[3].x = 7;
        team[3].y = 0;

        team.push_back(Piece());
        team[4].x = 0;
        team[4].y = 1;

        team.push_back(Piece());
        team[5].x = 2;
        team[5].y = 1;

        team.push_back(Piece());
        team[6].x = 4;
        team[6].y = 1;

        team.push_back(Piece());
        team[7].x = 6;
        team[7].y = 1;

        team.push_back(Piece());
        team[8].x = 1;
        team[8].y = 2;

        team.push_back(Piece());
        team[9].x = 3;
        team[9].y = 2;

        team.push_back(Piece());
        team[10].x = 5;
        team[10].y = 2;

        team.push_back(Piece());
        team[11].x = 7;
        team[11].y = 2;

        TEAM_NUMBER = BLACK_PIECE;
        ENEMY_TEAM_NUMBER = RED_PIECE;
    }
    else 
    {
         /* ====== DRUZYNA CZERWONA ====== */
        team.push_back(Piece());
        team[0].x = 0;
        team[0].y = 7;

        team.push_back(Piece());
        team[1].x = 2;
        team[1].y = 7;

        team.push_back(Piece());
        team[2].x = 4;
        team[2].y = 7;

        team.push_back(Piece());
        team[3].x = 6;
        team[3].y = 7;

        team.push_back(Piece());
        team[4].x = 1;
        team[4].y = 6;

        team.push_back(Piece());
        team[5].x = 3;
        team[5].y = 6;

        team.push_back(Piece());
        team[6].x = 5;
        team[6].y = 6;

        team.push_back(Piece());
        team[7].x = 7;
        team[7].y = 6;

        team.push_back(Piece());
        team[8].x = 0;
        team[8].y = 5;

        team.push_back(Piece());
        team[9].x = 2;
        team[9].y = 5;

        team.push_back(Piece());
        team[10].x = 4;
        team[10].y = 5;

        team.push_back(Piece());
        team[11].x = 6;
        team[11].y = 5;

        TEAM_NUMBER = RED_PIECE;
        ENEMY_TEAM_NUMBER = BLACK_PIECE;
    }

    for (int teamIndex = 0; teamIndex < team.size(); teamIndex++)
    {
        Board->virtualBoard[team[teamIndex].x][team[teamIndex].y] = topSide + 1;
    }
}

bool Player::makeMove(SDL_Event *)
{
    return false;
}

/**
 * Sprawdza czy pionki należą do tej samej drużyny
 * @return true jeśli są z tej samej drużyny, false w przeciwnym wypadku
 */
bool Player::sameTeam(int value1, int value2)
{
    if (value1%2 == value2%2 && value1 != EMPTY_PIECE) 
    {
        return true;
    }

    return false;
}

/**
 * Porusza pionkiem po planszy
 */
void Player::movePiece(vector<vector<int>> &pBoard, vector<Piece>& teamMove, int teamIndex, int newX, int newY)
{
    if (abs(newX - teamMove[teamIndex].x) == 2 && abs(newY - teamMove[teamIndex].y) == 2) 
    {
        killPiece(pBoard , abs(newX + teamMove[teamIndex].x)/2, abs(newY + teamMove[teamIndex].y)/2);
        killerPeiceIndex = teamIndex;
    }

    pBoard[newX][newY] = pBoard[teamMove[teamIndex].x][teamMove[teamIndex].y];
    pBoard[teamMove[teamIndex].x][teamMove[teamIndex].y] = EMPTY_PIECE;
    teamMove[teamIndex].x = newX;
    teamMove[teamIndex].y = newY;
}

/**
 * Zbija pionek
 */
void Player::killPiece(vector<vector<int>> &pBoard, int x, int y) 
{
    pBoard[x][y] = EMPTY_PIECE;
    killWasMade = true;
}

/**
 * Aktualizuje drużynę
 */
void Player::updateTeam() 
{
    bool updateMade = false;

    for (int index = 0; index < team.size(); index++)
    {
        if (!sameTeam(Board->virtualBoard[team[index].x][team[index].y], TEAM_NUMBER)) 
        {
            team.erase(team.begin()+index);
            index--;
            updateMade = true;
            cout << "Team:\t" << TEAM_NUMBER << "\thas a team.size():\t" << team.size() << endl;
        }
    }

    if (updateMade) 
    {
        cout << "*Team updated" << endl;
    }
}

/**
 * Aktualizuje królów
 */
void Player::updateKings() {

    int yToMakeKing = 7 * topSide;
    bool updateMade = false;

    for (int index = 0; index < team.size(); index++)
    {
        if (team[index].y == yToMakeKing && !team[index].isKing()) 
        {
            team[index].makeKing();
            Board->virtualBoard[team[index].x][team[index].y] += 2;
            updateMade = true;
        }
    }

    if (updateMade)
    {
        cout<<"*Kings updated"<<endl;
    }
}

/**
 * Oblicza indeks pionka po jego pozycji
 * @return indeks pionka
 */
int Player::pieceTeamIndexByXY(int x, int y) 
{
    int index = 0;

    while (index<team.size())
    {
        if ((team[index].x == x) && (team[index].y == y))
        {
            break;
        }

        index++;
    }

    return index;
}
