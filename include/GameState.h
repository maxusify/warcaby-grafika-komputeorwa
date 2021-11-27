#ifndef GAMESTATE_H
#define GAMESTATE_H

/* ====== KOMPILACJA ====== */
#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#endif

#ifdef __linux
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif
/* ======================== */

/* ========= IMPORTY ========= */
#include "AppState.h"
#include "Engine.h"
#include "AppStateManager.h"
#include "CheckersBoard.h"
#include "Player.h"
#include "AI.h"
#include "RealPlayer.h"
#include "Button.h"
#include "Texture.h"
/* =========================== */

/**
 * Typ wyliczeniowy wydzielający rodzaj pionka
 */ 
enum PiecesSprites {
    EMPTY_PIECE,
    RED_PIECE,
    BLACK_PIECE,
    RED_KING_PIECE,
    BLACK_KING_PIECE,
    TOTAL_PIECES
};

class AppStateManager;
class Button;
class CheckersBoard;
class Player;
class AI;
class Texture;

/** \class GameState
 *  \brief Klasa odpowiadająca za stan "W grze". Dziedziczy po AppState.
 */
class GameState : public AppState {
public:
    GameState();
    ~GameState();
    void stateEnter();
    void stateEvent();
    States stateUpdate();
    void stateRender();
    bool stateExit();

private:
    bool loadMedia();
    void setGameMode();
    bool gameOver();
    CheckersBoard *Board;
    Button *boardButtons;
    Player *Player1;
    Player *Player2;
    bool userQuit;
};

#endif /* GAMESTATE_H */
