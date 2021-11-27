#ifndef MENUSTATE_H
#define MENUSTATE_H

/* ====== KOMPILACJA ====== */
#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif
#ifdef __linux
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#endif
/* ======================== */

/* ========= IMPORTY ========= */
#include "AppState.h"
#include "Engine.h"
#include "Texture.h"
#include "Button.h"
/* =========================== */

class Button;

/*! \enum MenuSprites 
 *  Typ wyliczeniowy wydzielający używane tekstury w menu głównym
 */
enum MenuSprites {
    TWO_PLAYERS,
    SINGLE_PLAYER,
    AI_VS_AI,
    TWO_PLAYERS_HOVER,
    SINGLE_PLAYER_HOVER,
    AI_VS_AI_HOVER,
    FULL_MENU
};


/** \class MenuState
 *  \brief Klasa reprezentująca stan aplikacji w menu głównym. Dziedziczy po AppState.
 */ 
class MenuState : public AppState
{
public:
    MenuState();
    ~MenuState();
    void stateEnter();
    void stateEvent();
    States stateUpdate();
    void stateRender();
    bool stateExit();

private:
    bool hover[3] = {false, false, false};
    Button *boardButtons;
    void drawMenu();
    bool loadMedia();
    bool userQuit;
};

#endif /* MENUSTATE_H */
