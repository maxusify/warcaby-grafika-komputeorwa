#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#endif

#ifdef __linux
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif

using namespace std;
class AppStateManager;
class Texture;

/** class Engine
 *  brief Główna klasa reprezentująca silnik gry.
 *  details Pełni rolę kontrolera wszystkich pozostałych części gry
 *          oraz obsługuje biblioteki, ich moduły i zarządza nimi.
 */ 
class Engine 
{
public:
    Engine();
    ~Engine();

    int start();
    bool init();
    void close();
    int gameMode;

protected:
    AppStateManager *aps;
};

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern vector<SDL_Rect> spritesDims;
extern Texture spritesTexture;
extern int currentSprite;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int BUTTON_WIDTH;
extern int BUTTON_HEIGHT;
extern int TOTAL_BUTTONS;
extern int GAMEMODE;

#endif /* ENGINE_H */
